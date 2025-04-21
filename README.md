 # PROYECTO WEB SERVER 
### Integrantes: 
- Juan Esteban Barrios Tovar
- Alejandro García Cortés
- José Benjamín Vega Rámirez

## Descripción
En este proyecto, desarrollamos un servidor web, en c++, capaz de procesar peticiones GET, HEAD y POST, devolviendo recursos tipo html, videos e imágenes.

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
