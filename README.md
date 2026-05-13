# Proyecto Parqueadero

Sistema de parqueadero desarrollado en C++ usando sockets TCP.

## Tecnologías

- C++
- WinSock2
- GitHub
- VS Code

## Componentes

- Servidor TCP
- Cliente TCP
- Generador de placas
- UML del sistema

## Funcionalidades actuales

- Generación automática de placas
- Asignación de celdas
- Registro de entradas y salidas
- Comunicación cliente-servidor
- Envío automático cada 5 segundos

## Compilación

### Servidor

g++ main.cpp ServidorSocket.cpp GeneradorPlacas.cpp -o servidor -lws2_32

### Cliente

g++ main.cpp ClienteSocket.cpp -o cliente -lws2_32

## Ramas

- main
- desarrollo