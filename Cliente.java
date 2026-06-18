package libClases;

public class Cliente implements Proceso, Cloneable {
    
    // Static: Contador compartido
	
	
    private static int n = 1; // Se usa para asignar un código único a cada cliente

    private static Fecha fechaAltaPorDefecto = new Fecha(1, 1, 2018);

    // Atributos de instancia. 
    // NIF sí puede ser final porque String es inmutable en Java (se comporta como primitivo)
    private final String nif; 
    
    // IMPORTANTE: Quitamos 'final' de fechaNac para que funcione super.clone()
    // Si fuera final, no podríamos asignar una nueva fecha clonada.
    private int codCliente; 
    private String nombre; 
    private Fecha fechaNac; 
    private Fecha fechaAlta;

    // --- CONSTRUCTORES ---
    public Cliente(String NIF, String nom, Fecha fNac, Fecha fAlta) {
        codCliente = n++;
        nif = NIF;
        nombre = nom;
        // Copias profundas (Perfecto)
        fechaNac = new Fecha(fNac);
        fechaAlta = new Fecha(fAlta);
    }

    public Cliente(String NIF, String nom, Fecha fNac) {
        this(NIF, nom, fNac, fechaAltaPorDefecto);
    }

    // Constructor de copia
    public Cliente(Cliente c) {
        this.nif = c.nif;
        this.codCliente = n++; // Nuevo ID para la copia
        this.nombre = c.nombre;
        this.fechaNac = new Fecha(c.fechaNac);
        this.fechaAlta = new Fecha(c.fechaAlta);
    }

    // --- GETTERS Y SETTERS ---
    public void setNombre(String nombre) { this.nombre = nombre; }
    public String getNombre() { return this.nombre; }
    public String getNif() { return nif; }
    public int getCodCliente() { return codCliente; }

    // Getters con copia defensiva
    public Fecha getFechaNac() { return new Fecha(this.fechaNac); }
    public Fecha getFechaAlta() { return new Fecha(this.fechaAlta); }

    // Setter con copia defensiva
    public void setFechaAlta(Fecha nuevaFecha) { // DEPURACION--------------------------------
        // Evitamos guardar el puntero externo. Guardamos una copia.
        this.fechaAlta = new Fecha(nuevaFecha);
    }

    // ---MÉTODOS ESTÁTICOS ---
    public static void setFechaPorDefecto(Fecha fnueva) { // DEPURACION--------------------------------
        fechaAltaPorDefecto = new Fecha(fnueva); // Mejor guardar copia también aquí
    }
    public static Fecha getFechaPorDefecto() { 
        return new Fecha(fechaAltaPorDefecto); 
    }
    
    
    // ---OTROS MÉTODOS---
 // Método factura (dummy para herencia)
    
    public float factura() {
    	// TODO Auto-generated method stub

    	return 0; }
    
 // Método base para calcular la factura de un cliente. Las subclases deben sobrescribirlo
 	 // con su propia lógica dependiendo del tipo de cliente (p. ej., móvil, tarifa plana, etc.).


    // --- VISUALIZACIÓN ---

    
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Cliente cliente = (Cliente) obj;
        return nif.equals(cliente.nif);
    }

    
    public void ver() {
        System.out.println(this.toString());
    }

    
    public String toString() {
        // Usamos String.format para ser más limpios
        return String.format("%s %s: %s (%d - %s)", 
        		nif, fechaNac, nombre, codCliente, fechaAlta);
    }

    // --- CLONE ---
    
    
    public Object clone() { // La firma estándar devuelve Object
        Cliente obj = null;
        try {
            // 1. Copia superficial (copia los bits)
            obj = (Cliente) super.clone();
            
            // 2. Copia profunda (Deep Copy) de objetos mutables
            // Esto es necesario para que el clon tenga sus propias fechas
            obj.fechaNac = (Fecha) this.fechaNac.clone();
            obj.fechaAlta = (Fecha) this.fechaAlta.clone();
            
            // 3. Lógica específica de negocio (Nuevo ID para el clon)
            // Según tu PDF pág 31: "en el método clone... tendremos que incrementar dicho contador"
            obj.codCliente = n++; 
            
        } catch (CloneNotSupportedException e) {
            System.out.println("Error al clonar");
        }
        return obj;
    }
}
