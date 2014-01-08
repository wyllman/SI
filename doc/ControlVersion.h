/*
 *      Nombre: ControlVersion.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Registro de las versiones y los avances del proyecto.
 *
 */

/*
 *    Registro:
 *       v0.0:
 *              - Creada la estructura de clases inicial, usando el patrón
 *              Modelo-Vista-Controlador. Creadas las clases para la vista y el
 *              controlador.
 *              - Separación por carpetas los archivos de cabecera(.h) y los archivos de
 *              código(.cpp).
 *              - Arreglados los errores de enlazado de los archivos de cabecera en las
 *              nuevas carpetas.
 *              - Creadas las funciones virtuales de las clases Model, View y Controller
 *              para el uso del polimorfismo.
 *              - Enlazada la clase Director (como un hijo de Controller) con sus herremientas
 *              FileLog y MainLoop.
 *              - En la función main (): Creado un puntero a Controller con un objeto de tipo
 *              Director y comprobado ciclo de llamadas a constructores y destructores.
 *              - Enlazada con el programa principal la clase Interface (hija de View).
 *              - Creadas la clase Simulator (hija de Model) y enlazada con el programa
 *              principal.
 *              - Enlazados los gestores Bureaucrat y Scenographer a la clase Interface.
 *              - Enlazadas las herramientas Window, Context y Scene a la clase Interfeace.
 *
 *       v0.001:
 *              - Implementada la primera versión de la clase FileLog con funciones básicas:
 *                 init(), reset() y showConsole().
 *              - Usando el archivo Tools.h se activa o desactiva el mostrado de mensajes en
 *              consola o el uso del registro de acciones-errores.
 *              - Uso de la clase FileLog por todos los metodos que requieran ser registrados.
 *              - Implementada la función save() de la clase FileLog.
 *              - Implementación inicial la clase MainLoop, Interface, Window y Bureaucrat.
 *              - Implementada la parte de la interfaz hasta la creación de una ventana SDL.
 *              - Implementado en el bucle principal de Director la acción de parar la ejecución
 *              al cerrarse la ventana SDL creada(Captura evento SDL).
 *              - Implementación inicial la clase Context.
 *              - Implementada la inicialización de OGL, los shaders y una visualización inicial
 *              de puntos.
 *
 *       v0.002:
 *              - Implementadas las funciones logAction() para la clase Director y el progrma
 *              principal. Usadas para separar las acciones referentes al registro de mensajes
 *              internos del resto del código.
 *              - Implementadas las funciones logAction() para el resto de clases.
 *              - Implementada una primera versión de las clases Scene y Scenographer
 *              (proyección, cámara y suelo).
 *              - Mezcla de la rama guillermo (estructura de clases del MVC) con la rama master
 *              (estructura inicial del sist. int.).
 *              - Principales arreglos de enlazado después de la reestructuración o mezcla.
 *              - Enlazando la clase Map con la clase Simulator y su función init(). Además
 *              se muestra por consola el mapa generado.
 *              - Refactorizado de los "includes" del proyecto.
 *              - Creada la visualización gráfica(OGL) del mapa.
 *              - Creados los movimientos de cámara básicos (Zoom y desplazamiento en eje X).
 *
 *       v0.003:
 *              - Reorganizada la ejecución de las llamadas en PreColonia.cpp (la llamada a la
 *                función stop() de la vista y el modelo se realiza desde la función stop() de
 *                la clase controlador).
 *              - Cambiado el movimiento de la cámara en el eje X por uno de rotación alrededor
 *                del punto central del mapa.
 *              - Eliminados los Quads interiores de la representación gráfica del terreno.
 *              - Refactorización para la mejora del uso de los buffer de vertices y colores.
 *              - Representación gráfica del agente principal creada.
 *              - Representación gráfica de los agentes exploradores y trabajadores.
 *              - Coordinar la información del agente principal y los exploradores con su
 *                representación gráfica.
 *              - Coordinada la información de los agentes trabjajadores con su representación
 *                gráfica.
 */

