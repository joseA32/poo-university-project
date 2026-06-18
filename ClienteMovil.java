package libClases;

public class ClienteMovil extends Cliente {

    // --- ATRIBUTOS ---
    private float minutosHablados;
    private float precioMinuto;
    private Fecha fechaPermanencia; //// fecha fin permanencia. Mutable -> Ojo con los clones

    // --- CONSTRUCTORES ---

    // 1. Completo (Con fecha permanencia explícita)
    public ClienteMovil(String nif, String nom, Fecha fNac, Fecha fAlta, Fecha fPer, float minutos, float precio) {
        super(nif, nom, fNac, fAlta);
        this.minutosHablados = minutos;
        this.precioMinuto = precio;
        // Copia profunda de la permanencia
        this.fechaPermanencia = new Fecha(fPer);
    }

    // 2. Sin Permanencia explícita (Calculamos Alta + 1 año)
    public ClienteMovil(String nif, String nom, Fecha fNac, Fecha fAlta, float minutos, float precio) {
        super(nif, nom, fNac, fAlta);
        this.minutosHablados = minutos;
        this.precioMinuto = precio;
        
        // Calculamos permanencia: Alta + 1 año
        // Usamos getFechaAlta() (que ya nos da una copia segura) para leer los datos
        Fecha alta = getFechaAlta();
        this.fechaPermanencia = new Fecha(alta.getDia(), alta.getMes(), alta.getAnio() + 1);
    }

    // 3. Sin Alta ni Permanencia (Usa alta por defecto y permanencia por defecto)
    public ClienteMovil(String nif, String nom, Fecha fNac, float minutos, float precio) {
        super(nif, nom, fNac); // Esto asigna la fecha alta por defecto (01/01/2018)
        this.minutosHablados = minutos;
        this.precioMinuto = precio;
        
        // Calculamos permanencia basada en la fecha de alta (que será la de defecto)
        Fecha alta = getFechaAlta();
        this.fechaPermanencia = new Fecha(alta.getDia(), alta.getMes(), alta.getAnio() + 1);
    }

    // Constructor de Copia
    public ClienteMovil(ClienteMovil c) {
        super(c);
        this.minutosHablados = c.minutosHablados;
        this.precioMinuto = c.precioMinuto;
        this.fechaPermanencia = new Fecha(c.fechaPermanencia); // Copia profunda
    }

    // --- GETTERS Y SETTERS ---

    public float getMinutos() { return minutosHablados; }
    public void setMinutos(float m) { this.minutosHablados = m; }

    public float getPrecioMinuto() { return precioMinuto; }
    public void setPrecioMinuto(float p) { this.precioMinuto = p; }

    // ¡Copia Defensiva!
    public Fecha getFPermanencia() {
        return new Fecha(fechaPermanencia);
    }

    public void setFPermanencia(Fecha f) {
        this.fechaPermanencia = new Fecha(f);
    }

    // ---OTROS MÉTODOS---
    public float factura() {
        // Calculamos el total de la factura
    	return minutosHablados * precioMinuto;
    }

    
    
    // --- SOBRESCRITURA DE MÉTODOS DE VISUALIZACIÓN ---

    
    public Object clone() {
        // Aquí SÍ necesitamos lógica extra porque tenemos una Fecha nueva
        ClienteMovil clon = (ClienteMovil) super.clone(); // Llama a Cliente.clone() (ID nuevo, fechas base copiadas)
        
        // Ahora arreglamos NUESTRA fecha (la de permanencia)
        // Como clone devuelve Object, hay que hacer cast a Fecha si usas clone, 
        // o usar constructor de copia. Usando clone() como pide la práctica:
        clon.fechaPermanencia = (Fecha) this.fechaPermanencia.clone();
        
        return clon;
    }

    
    public String toString() {
        return super.toString() + " " + fechaPermanencia + " " + minutosHablados + " x " + precioMinuto+ " --> " + factura();
    }
}


