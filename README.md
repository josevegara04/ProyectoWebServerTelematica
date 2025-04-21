# PROYECTO WEB SERVER 
### Integrantes: 
- Juan Esteban Barrios Tovar
- Alejandro García Cortés
- José Benjamín Vega Rámirez

## Descripción
Este proyecto tiene como objetivo desarrollar un servidor web básico utilizando el lenguaje de programación **C++**, capaz de manejar solicitudes HTTP como **GET**, **HEAD** y **POST**. El servidor puede enviar archivos estáticos como páginas HTML, imágenes y videos. Se buscó simular el comportamiento básico de un servidor como Apache, pero a un nivel de bajo nivel usando sockets TCP.

## Desarrollo / Implementación

La lógica principal del proyecto fue desarrollada en `server.cpp`. El servidor escucha peticiones en el puerto 8080 y responde dependiendo del método HTTP y del recurso solicitado. La estructura de carpetas incluye:
ProyectoWebServerTelematica/
├── server.log
├── server.cpp
├── client.cpp
├── templates/
│   ├── case1.html
│   ├── case2.html
│   ├── case3.html
│   ├── case4.html
│   ├── logo.jpg
│   └── style.css
│   ├── archivo.mp4
│   ├── index.html

El servidor fue implementado usando Winsock2 para manejo de conexiones TCP en Windows.
Se incluye funcionalidad para:

- Analizar solicitudes HTTP y extraer el método y el recurso solicitado.

- Buscar el archivo correspondiente dentro de la carpeta templates.

- Determinar el tipo MIME y responder adecuadamente con cabeceras HTTP válidas.

- Registrar logs de cada solicitud en server.log.




## Proceso para ejecutar el servidor
1) **Crea una carpeta en donde puedas guardar el proyecto**
   
2) **Clonar el repositorio**
   
   Abre GitBash y navega hasta la carpeta que creaste y escribe el siguiente comando:
   ```
   git clone https://github.com/josevegara04/ProyectoWebServerTelematica.git
   ```

3) **Ejecuta el servidor**
   
   En la terminal, navega hasta la carpeta del proyecto. Después, ejecuta el siguiente comando:
   > en Windows
   ```
   server 8080 server.log templates
   ```
   > en PowerShell
   ```
   ./server 8080 server.log templates
   ```

Después de seguir estos pasos, el servidor estará funcionando, mostrando este mensaje: 

```
   Servidor escuchando en el puerto 8080...
```

Para probar el servidor, puedes ingrear a localhost:8080.
Para probar los 4 casos de pruba, prueba con los sigueientes endpoints:
- /case1
- /case2
- /case3
- /case4

## Capturas del funcionamiento:
1) **Case 1**

![image](https://github.com/user-attachments/assets/af3eb9ed-da66-4c3b-8b7b-64a0db6e68db)

2) **Case 2**
   ![image](https://github.com/user-attachments/assets/d02688cf-9aa5-4282-ab5c-2d9cb2684255)

3) **Case 3**
   ![image](https://github.com/user-attachments/assets/c4fc0e2d-90e1-4790-a8c1-7a083fa154d6)

4) **Case 4**
   ![image](https://github.com/user-attachments/assets/8205ca72-762c-4802-a665-6f7c3e18ad6e)

5) **Index**
   ![image](https://github.com/user-attachments/assets/80563930-61f8-439c-b45e-5549ee6efc7e)

6) **Server.log**
![image](https://github.com/user-attachments/assets/0951eb31-94ce-4b98-9a03-fc1228ce6175)



## Conclusiones:
- Fue posible implementar un servidor web funcional en C++ desde cero.
- Aprendimos a usar sockets TCP con Winsock2 y a gestionar cabeceras HTTP.
- La arquitectura cliente-servidor quedó claramente evidenciada en la práctica.

## Referencias:
- Documentación oficial de Winsock2 - Microsoft
- RFC 2616 - HTTP/1.1
- C++ Reference: https://cplusplus.com/


   


