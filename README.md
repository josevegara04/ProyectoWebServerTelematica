![image](https://github.com/user-attachments/assets/effb6388-bb05-4b22-9f6e-fce0c6652b46) # PROYECTO WEB SERVER 
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
   2025-04-15 16:15:37 | 127.0.0.1 | GET | /index | 200
2025-04-15 16:15:37 | 127.0.0.1 | GET | /style.css | 200
2025-04-15 16:15:37 | 127.0.0.1 | GET | /images.jpg | 200
2025-04-15 16:15:37 | 127.0.0.1 | GET | /Testeo_3.mp4 | 200
2025-04-15 16:20:04 | 127.0.0.1 | GET | /index | 200
2025-04-15 16:20:04 | 127.0.0.1 | GET | /style.css | 200
2025-04-15 16:20:04 | 127.0.0.1 | GET | /images.jpg | 200
2025-04-15 16:20:04 | 127.0.0.1 | GET | /Testeo_3.mp4 | 200
2025-04-15 16:20:07 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-15 16:48:44 | 127.0.0.1 | HEAD | /index | 200
2025-04-16 09:50:57 | 127.0.0.1 | GET | /index | 200
2025-04-16 09:51:22 | 127.0.0.1 | GET | /index | 200
2025-04-16 09:51:22 | 127.0.0.1 | GET | /style.css | 200
2025-04-16 09:51:23 | 127.0.0.1 | GET | /images.jpg | 200
2025-04-16 09:51:23 | 127.0.0.1 | GET | /Testeo_3.mp4 | 200
2025-04-16 09:51:24 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-16 09:53:17 | 127.0.0.1 | POST | /submit | 400
2025-04-16 10:29:49 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:29:49 | 127.0.0.1 | GET | /templates/images.jpg | 404
2025-04-16 10:31:02 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:31:02 | 127.0.0.1 | GET | /templates/images.jpg | 404
2025-04-16 10:31:04 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:31:04 | 127.0.0.1 | GET | /templates/images.jpg | 404
2025-04-16 10:32:15 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:32:15 | 127.0.0.1 | GET | /images.jpg | 404
2025-04-16 10:33:59 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:33:59 | 127.0.0.1 | GET | /images.jpg | 404
2025-04-16 10:35:00 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:35:00 | 127.0.0.1 | GET | /images.jpg | 404
2025-04-16 10:35:38 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:36:44 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:36:50 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:36:50 | 127.0.0.1 | GET | /images.jpg | 404
2025-04-16 10:37:38 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:37:39 | 127.0.0.1 | GET | /images.jpg | 404
2025-04-16 10:39:20 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 10:39:20 | 127.0.0.1 | GET | /static/images.jpg | 404
2025-04-16 10:39:40 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 11:23:32 | 127.0.0.1 | GET | /index | 404
2025-04-16 11:23:56 | 127.0.0.1 | GET | / | 200
2025-04-16 11:24:04 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 11:24:04 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 11:25:30 | 127.0.0.1 | GET | /case1 | 200
2025-04-16 11:25:30 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 11:30:51 | 127.0.0.1 | GET | /case2 | 404
2025-04-16 11:31:03 | 127.0.0.1 | GET | /case2 | 404
2025-04-16 11:31:19 | 127.0.0.1 | GET | /case2 | 404
2025-04-16 11:31:20 | 127.0.0.1 | GET | /case2 | 404
2025-04-16 11:31:21 | 127.0.0.1 | GET | /case2 | 404
2025-04-16 11:32:23 | 127.0.0.1 | GET | /case2 | 200
2025-04-16 11:32:24 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 11:33:58 | 127.0.0.1 | GET | /case3 | 200
2025-04-16 11:33:58 | 127.0.0.1 | GET | /styles/style.css | 200
2025-04-16 11:33:58 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 11:33:58 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 11:34:26 | 127.0.0.1 | GET | /case3 | 200
2025-04-16 11:34:26 | 127.0.0.1 | GET | /styles/style.css | 200
2025-04-16 11:34:26 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 11:34:27 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 11:35:17 | 127.0.0.1 | GET | /case4 | 200
2025-04-16 11:35:17 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 12:35:24 | 127.0.0.1 | GET | / | 200
2025-04-16 12:35:25 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-16 12:35:58 | 127.0.0.1 | GET | / | 200
2025-04-16 12:37:09 | 127.0.0.1 | GET | / | 200
2025-04-16 12:38:20 | 127.0.0.1 | GET | /index | 404
2025-04-16 12:38:31 | 127.0.0.1 | GET | /index.html | 200
2025-04-16 12:38:55 | 127.0.0.1 | GET | /case1.html | 200
2025-04-16 12:38:55 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 12:39:15 | 127.0.0.1 | GET | /case2.html | 200
2025-04-16 12:39:15 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 12:39:28 | 127.0.0.1 | GET | /case3.html | 200
2025-04-16 12:39:28 | 127.0.0.1 | GET | /styles/style.css | 200
2025-04-16 12:39:28 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 12:39:28 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 12:39:35 | 127.0.0.1 | GET | /case4.html | 200
2025-04-16 12:39:35 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 12:40:00 | 127.0.0.1 | GET | /index.html | 200
2025-04-16 17:09:39 | 127.0.0.1 | GET | /index | 404
2025-04-16 17:09:39 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-16 17:10:03 | 127.0.0.1 | GET | /index | 404
2025-04-16 17:15:05 | 127.0.0.1 | GET | /index | 404
2025-04-16 17:15:05 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-16 17:15:10 | 127.0.0.1 | GET | /index.html | 200
2025-04-16 17:15:31 | 127.0.0.1 | GET | /case1.html | 200
2025-04-16 17:15:31 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 17:15:53 | 127.0.0.1 | GET | /case2.html | 200
2025-04-16 17:15:53 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 17:15:58 | 127.0.0.1 | GET | /case3.html | 200
2025-04-16 17:15:58 | 127.0.0.1 | GET | /styles/style.css | 200
2025-04-16 17:15:58 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-16 17:15:58 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-16 17:16:05 | 127.0.0.1 | GET | /cas4.html | 404
2025-04-16 17:16:09 | 127.0.0.1 | GET | /case4.html | 200
2025-04-16 17:16:09 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:24:30 | 127.0.0.1 | GET | / | 200
2025-04-21 09:24:30 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-21 09:24:37 | 127.0.0.1 | GET | /case1 | 200
2025-04-21 09:24:37 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:24:43 | 127.0.0.1 | GET | /case1.html | 200
2025-04-21 09:24:43 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:24:46 | 127.0.0.1 | GET | /case1 | 200
2025-04-21 09:24:46 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:26:35 | 127.0.0.1 | GET | /case2 | 200
2025-04-21 09:26:35 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-21 09:27:38 | 127.0.0.1 | GET | /case3 | 200
2025-04-21 09:27:38 | 127.0.0.1 | GET | /styles/style.css | 200
2025-04-21 09:27:38 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:27:38 | 127.0.0.1 | GET | /videos/Testeo_3.mp4 | 200
2025-04-21 09:28:23 | 127.0.0.1 | GET | /case4 | 200
2025-04-21 09:28:23 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:28:49 | 127.0.0.1 | GET | /index | 404
2025-04-21 09:28:49 | 127.0.0.1 | GET | /index | 404
2025-04-21 09:28:57 | 127.0.0.1 | GET | /index.html | 200
2025-04-21 09:32:04 | 127.0.0.1 | GET | / | 200
2025-04-21 09:32:22 | 127.0.0.1 | GET | / | 200
2025-04-21 09:32:37 | 127.0.0.1 | GET | /index | 404
2025-04-21 09:32:39 | 127.0.0.1 | GET | /case1 | 200
2025-04-21 09:32:39 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:32:48 | 127.0.0.1 | GET | / | 200
2025-04-21 09:33:08 | 127.0.0.1 | GET | / | 200
2025-04-21 09:34:03 | 127.0.0.1 | GET | /case1 | 200
2025-04-21 09:34:03 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:34:40 | 127.0.0.1 | GET | /case1.html | 200
2025-04-21 09:34:40 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:35:02 | 127.0.0.1 | GET | / | 200
2025-04-21 09:35:31 | 127.0.0.1 | GET | /case1.html | 200
2025-04-21 09:35:31 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:35:32 | 127.0.0.1 | GET | /favicon.ico | 404
2025-04-21 09:35:33 | 127.0.0.1 | GET | /case1.html | 200
2025-04-21 09:35:33 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:35:34 | 127.0.0.1 | GET | /case1.html | 200
2025-04-21 09:35:34 | 127.0.0.1 | GET | /case1.html | 200
2025-04-21 09:35:34 | 127.0.0.1 | GET | /images/logo.jpg | 200
2025-04-21 09:35:34 | 127.0.0.1 | GET | /favicon.ico | 404


## Conclusiones:
- Fue posible implementar un servidor web funcional en C++ desde cero.
- Aprendimos a usar sockets TCP con Winsock2 y a gestionar cabeceras HTTP.
- La arquitectura cliente-servidor quedó claramente evidenciada en la práctica.
- 
## Referencias:
- Documentación oficial de Winsock2 - Microsoft
- RFC 2616 - HTTP/1.1
- C++ Reference: https://cplusplus.com/


   


