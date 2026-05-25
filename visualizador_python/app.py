import socket
import streamlit as st
from streamlit_autorefresh import st_autorefresh
from datetime import datetime
import pandas as pd
from io import BytesIO
import base64

def play_sound(file_path):

    with open(file_path, "rb") as f:
        audio_bytes = f.read()

    b64 = base64.b64encode(audio_bytes).decode()

    audio_html = f"""
        <audio autoplay>
            <source src="data:audio/mp3;base64,{b64}" type="audio/mp3">
        </audio>
    """

    st.markdown(audio_html, unsafe_allow_html=True)

def generar_excel(historial):

    datos = []

    for evento in historial:

        partes = evento.split(" | ")

        if len(partes) == 4:

            datos.append({
                "Hora": partes[0],
                "Placa": partes[1],
                "Tipo": partes[2],
                "Celda": partes[3].replace("Celda ", "")
            })

    df = pd.DataFrame(datos)

    output = BytesIO()

    with pd.ExcelWriter(output, engine='openpyxl') as writer:
        df.to_excel(writer, index=False, sheet_name="Historial")

    output.seek(0)

    return output

# Auto refresco cada 2 segundos
st_autorefresh(interval=2000, key="refresh")

st.set_page_config(
    page_title="Parqueadero",
    layout="wide"
)

st.title("Sistema de Parqueadero")
st.markdown("""
<style>
    .block-container {
        padding-top: 1rem;
    }

    div[data-testid="stVerticalBlock"] {
        gap: 0.5rem;
    }
</style>
""", unsafe_allow_html=True)

# Crear estados iniciales
if "parqueadero" not in st.session_state:
    st.session_state.parqueadero = {}

if "horas_entrada" not in st.session_state:
    st.session_state.horas_entrada = {}
    
if "historial" not in st.session_state:
    st.session_state.historial = []

  
# Crear socket una sola vez
if "cliente" not in st.session_state:

    cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    cliente.connect(("127.0.0.1", 8080))
    cliente.setblocking(False)

    st.session_state.cliente = cliente

# Recibir datos
try:
    mensaje = st.session_state.cliente.recv(1024).decode().strip()

    if mensaje:

        placa, tipo, hora_entrada, celda = mensaje.split(",")
        celda = int(celda)

        if tipo == "ENTRADA":
            st.session_state.parqueadero[celda] = placa
            st.session_state.horas_entrada[celda] = hora_entrada
            play_sound("sounds/entrada.mp3")

        elif tipo == "SALIDA":

            if celda in st.session_state.parqueadero:
                placa = st.session_state.parqueadero[celda]
                del st.session_state.parqueadero[celda]

            if celda in st.session_state.horas_entrada:
                del st.session_state.horas_entrada[celda]
            
            play_sound("sounds/salida.mp3")

        evento = f"{hora_entrada} | {placa} | {tipo} | Celda {celda}"

        st.session_state.historial.insert(0, evento)
        st.session_state.historial = st.session_state.historial[:]

        st.success(f"{tipo}: {placa}")

except:
    st.success("🚗 ... 🚗")

# Métricas


ocupadas = len(st.session_state.parqueadero)

libres = 10 - ocupadas

porcentaje = (ocupadas / 10) * 100

st.markdown("### Ocupación del sistema")

st.progress(ocupadas / 10)

col1, col2, col3 = st.columns(3)

col1.metric("Celdas Ocupadas", ocupadas)

col2.metric("Celdas Libres", libres)

col3.metric("Ocupación", f"{porcentaje:.0f}%")

seccion = st.radio(
    "Navegación",
    ["Dashboard", "Historial", "Vehículos Activos"],
    horizontal=True
)

if seccion == "Dashboard":
    # Mostrar parqueadero
    st.markdown("## 🖥️ CONTROL PARKING SYSTEM")
    if ocupadas == 10:
        st.error("🚨 ALERTA: PARQUEADERO SATURADO")
        play_sound("sounds/full.mp3")

    elif ocupadas >= 7:
        st.warning("⚠️ ALTA OCUPACIÓN DETECTADA")

    else:
        st.success("🟢 SISTEMA OPERATIVO NORMAL")

    columnas = st.columns(5)

    for i in range(1, 11):

        ocupado = i in st.session_state.parqueadero

        if ocupado:

            placa = st.session_state.parqueadero[i]

            html = f"""
            <div style="
                background-color:#b30000;
                box-shadow: 0px 0px 12px rgba(255,0,0,0.6);
                padding:20px;
                border-radius:15px;
                text-align:center;
                color:white;
                margin-bottom:15px;
            ">
                <h3>Celda {i}</h3>
                <h2>🚗</h2>
                <p><b>{placa}</b></p>
                <p>OCUPADA</p>
            </div>
            """

        else:

            html = f"""
            <div style="
                background-color:#0a8f3c;
                box-shadow: 0px 0px 12px rgba(0,255,120,0.3);
                padding:20px;
                border-radius:15px;
                text-align:center;
                color:white;
                margin-bottom:15px;
            ">
                <h3>Celda {i}</h3>
                <h2>✅</h2>
                <p>LIBRE</p>
            </div>
            """

        columnas[(i - 1) % 5].markdown(
            html,
            unsafe_allow_html=True
        )


if seccion == "Historial":
    st.subheader("Historial de Movimientos")
    st.caption("Registro en tiempo real de entradas y salidas del parqueadero")

    if len(st.session_state.historial) == 0:
        st.info("No hay movimientos aún")

    else:

        datos = []

        for evento in st.session_state.historial:

            partes = evento.split(" | ")

            if len(partes) == 4:

                datos.append({
                    "Hora": partes[0],
                    "Placa": partes[1],
                    "Tipo": partes[2],
                    "Celda": partes[3].replace("Celda ", "")
                })

        st.dataframe(
            datos,
            width = "stretch",
            hide_index=True
        )
        excel_file = generar_excel(st.session_state.historial)

        st.download_button(
            label="📥 Descargar historial en Excel",
            data=excel_file,
            file_name="historial_parqueadero.xlsx",
            mime="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"
        )


if seccion == "Vehículos Activos":
    st.subheader("Vehículos Activos")

    if len(st.session_state.parqueadero) == 0:

        st.info("No hay vehículos en el parqueadero")

    else:

        for celda, placa in st.session_state.parqueadero.items():

            hora_entrada = st.session_state.horas_entrada.get(
                celda)
            
            if hora_entrada is None:
                continue

            try:

                formato = "%H:%M:%S"

                inicio = datetime.strptime(
                    hora_entrada,
                    formato
                )

                ahora = datetime.now()

                inicio = inicio.replace(
                    year=ahora.year,
                    month=ahora.month,
                    day=ahora.day
                )

                diferencia = ahora - inicio

                minutos = int(diferencia.total_seconds() // 60)

                segundos = int(diferencia.total_seconds() % 60)

                tiempo_estacionado = f"{minutos} min {segundos} seg"

            except:

                tiempo_estacionado = "Calculando..."

            st.markdown(f"""
            <div style="
                background-color:#262730;
                padding:15px;
                border-radius:12px;
                margin-bottom:10px;
                color:white;
            ">
                <h4>🚗 {placa}</h4>
                <p><b>Celda:</b> {celda}</p>
                <p><b>Hora entrada:</b> {hora_entrada}</p>
                <p><b>Tiempo estacionado:</b> {tiempo_estacionado}</p>
            </div>
            """, unsafe_allow_html=True)