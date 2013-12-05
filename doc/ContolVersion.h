/*
 *      Nombre: ContolVersion.h
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
 */

