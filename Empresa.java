package libClases;

import java.util.Scanner;

public class Empresa implements Cloneable, Proceso {
    
    // --- ATRIBUTOS ---
    // Usamos un array nativo y lo redimensionamos manualmente
    private Cliente[] clientes;
    private int nClientes; // Número real de clientes guardados
    private int NMax;      // Capacidad actual del array
    private final int INCREMENTO = 5; // Cuánto crece el array cada vez

    // --- CONSTRUCTORES ---
    public Empresa() {
        this.clientes = new Cliente[INCREMENTO];
        this.nClientes = 0;
        this.NMax = INCREMENTO;
    }

    // --- CLONE (Gestión de memoria dinámica manual) ---
   
    public Object clone() {
        Empresa obj = null;
        try {
            obj = (Empresa) super.clone();
            // 1. Clonamos el array (el contenedor)
            obj.clientes = this.clientes.clone();
            
            // 2. Clonamos CADA cliente de dentro (Deep Copy)
            // Si no hacemos esto, la empresa clonada apuntaría a los mismos clientes (punteros compartidos)
            for (int i = 0; i < nClientes; i++) {
                obj.clientes[i] = (Cliente) this.clientes[i].clone();
            }
        } catch (CloneNotSupportedException ex) {
            System.out.println("No se ha podido clonar \n");
        }
        return obj;
    }

    // --- MÉTODOS DE GESTIÓN (ALTA/BAJA) ---

    // Método auxiliar para buscar la posición de un cliente
    public final int buscarCliente(String dni) {
        for (int i = 0; i < nClientes; i++) {
            if (clientes[i].getNif().equals(dni)) {
                return i; // Lo hemos encontrado en la posición i
            }
        }
        return -1; // No existe
    }

    // ALTA: Añadir cliente (con redimensionado dinámico tipo realloc)
    public void alta(Cliente c) {
        int pos = buscarCliente(c.getNif());
        
        if (pos == -1) { // Solo si no existe ya
            // Si el array está lleno, lo ampliamos
            if (nClientes == NMax) {
                NMax += INCREMENTO;
                Cliente[] tablaNueva = new Cliente[NMax];
                
                // Copiamos los punteros del array viejo al nuevo
                for (int i = 0; i < nClientes; i++) {
                    tablaNueva[i] = clientes[i];
                }
                clientes = tablaNueva; // Cambiamos la referencia al nuevo array más grande
            }
            
            // Añadimos el nuevo cliente al final
            clientes[nClientes] = c;
            nClientes++;
        } 
        
    }

    // BAJA: Eliminar cliente (moviendo los huecos a la izquierda)
    public void baja(String dni) {
        int pos = buscarCliente(dni);
        if (pos != -1) {
            // Desplazamos todos los clientes una posición a la izquierda para tapar el hueco
            for (int i = pos; i < nClientes - 1; i++) {
                clientes[i] = clientes[i + 1];
            }
            // Borramos la última referencia duplicada y bajamos el contador
            nClientes--;
            clientes[nClientes] = null; // Limpieza (buena práctica en Java)
        } 
        
    }

    // --- MÉTODOS INTERACTIVOS (PIDEN DATOS AL USUARIO) ---

    public void alta() {
        Scanner s = new Scanner(System.in);
        System.out.print("DNI: ");
        String dni = s.nextLine();
        
        if (buscarCliente(dni) != -1) {
            System.out.println("Ya existe un cliente con este DNI\n" + clientes[buscarCliente(dni)] + "\n");
        } else {
            System.out.print("Indique el nombre del cliente: ");
            String nombre = s.nextLine();
            
            System.out.println("Fecha de nacimiento: "); // Fecha.pedirFecha ya tiene sus propios prints
            Fecha fNac = Fecha.pedirFecha();
            
            System.out.println("Fecha de alta: ");
            Fecha fAlta = Fecha.pedirFecha();
            
            System.out.print("Indique los minutos que habla al mes: ");
            float min = s.nextFloat(); // OJO: Usar coma decimal en consola española
            
            System.out.print("Indique el tipo de cliente (1-Móvil, 2-Tarifa Plana): ");
            int tipo = s.nextInt();
            
            // LIMPIEZA DE BUFFER: Después de leer números (nextInt/Float), queda un Enter colgado.
            // Si viene un nextLine luego, se lo come. Limpiamos aquí por si acaso.
            s.nextLine(); 

            if (tipo == 1) {
                System.out.print("Indique el precio por minuto: ");
                float precio = s.nextFloat();
                
                System.out.println("Fecha fin permanencia: ");
                Fecha fPerman = Fecha.pedirFecha();
                
                // Creamos el objeto y lo mandamos al otro método alta
                alta(new ClienteMovil(dni, nombre, fNac, fAlta, fPerman, min, precio));
                
            } else if (tipo == 2) {
            	
                System.out.print("Nacionalidad: ");
                String nacionalidad = s.nextLine(); // Aquí es donde fallaría si no hubiéramos limpiado el buffer antes
                
                alta(new ClienteTarifaPlana(dni, nombre, fNac, fAlta, min, nacionalidad));
            }
        }
        //s.close(); //No cerramos el Scanner 's' para no cerrar System.in
    }

    public void baja() {
        Scanner s = new Scanner(System.in);
        // CAMBIO 1: Texto exacto del PDF 
        System.out.print("Introduzca nif cliente a dar de baja: ");
        String dni = s.nextLine();
        
        int pos = buscarCliente(dni);
        if (pos != -1) {
            System.out.println(clientes[pos]); // Muestra el cliente encontrado
            
            char confirm;
            do {
                // CAMBIO 2: Texto exacto con interrogación al principio [cite: 78]
                System.out.print("¿Seguro que desea eliminarlo (s/n)? ");
                // next().charAt(0) lee el carácter, pero deja un salto de línea. 
                // No pasa nada porque el bucle limpia o el método acaba.
                confirm = s.next().charAt(0); 
            } while (confirm != 's' && confirm != 'S' && confirm != 'n' && confirm != 'N');
            
            if (confirm == 's' || confirm == 'S') {
                // TRUCO IMPORTANTE: Guardamos el nombre ANTES de borrar.
                // Si borras primero con baja(dni), el array se mueve y clientes[pos] 
                // pasaría a ser el siguiente cliente o null.
                String nombreBorrado = clientes[pos].getNombre();
                
                baja(dni); // Borramos lógicamente
                
                // CAMBIO 3: Mensaje detallado como pide el PDF 
                System.out.println("El cliente " + nombreBorrado + " con nif " + dni + " ha sido eliminado");
            } else {
                // CAMBIO 4: Mensaje con NIF como pide el PDF 
                System.out.println("El cliente con nif " + dni + " no se elimina");
            }
        } else {
            // Este mensaje no sale explícito en la salida del PDF de ejemplo, 
            // pero tu versión es correcta y clara.
            System.out.println("Este DNI no existe \n");
        }
        // No cerramos el scanner s para no matar System.in
    }
    // --- CÁLCULOS Y CONSULTAS ---

    public void descuento(int dto) {
        for (int i = 0; i < nClientes; i++) {
            // RTTI / Dynamic Cast seguro
            if (clientes[i] instanceof ClienteMovil) {
                ClienteMovil cm = (ClienteMovil) clientes[i];
                // CORRECCIÓN: Usamos getPrecioMinuto/setPrecioMinuto (nombres de nuestra clase)
                float nuevoPrecio = cm.getPrecioMinuto() * (1 - dto / 100f);
                cm.setPrecioMinuto(nuevoPrecio);
            }
        }
    }

    public float factura() {
        float total = 0;
        for (int i = 0; i < nClientes; i++) {
            total += clientes[i].factura(); // Polimorfismo
        }
        return total;
    }
    
    public int getN() {
        return nClientes;
    }

    public int nClienteMovil() {
        int n = 0;
        for (int i = 0; i < nClientes; i++) {
            if (clientes[i] instanceof ClienteMovil) {
                n++;
            }
        }
        return n;
    }

    // --- VISUALIZACIÓN ---

   
    public void ver() {
        System.out.println(this.toString());
    }

    
    public String toString() {
        // StringBuilder es mucho más eficiente que concatenar Strings con +
        StringBuilder s = new StringBuilder();
        for (int i = 0; i < nClientes; i++) {
            s.append(clientes[i].toString()).append("\n");
        }
        return s.toString();
    }
}