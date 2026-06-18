package libClases;

public class ClienteTarifaPlana extends Cliente { // 'implements Cloneable' se hereda
    
    // ATRIBUTOS ESTÁTICOS (Compartidos por todos)
    // Según enunciado: 300 min por 20 euros por defecto 
    private static float tarifa = 20f;
    private static float limite = 300f;
    
    // ATRIBUTOS DE INSTANCIA
    private float minutosHablados;
    private String nacionalidad;

    // --- CONSTRUCTORES ---

    // Constructor completo
    public ClienteTarifaPlana(String nif, String nom, Fecha fNac, Fecha fAlta, float minutos, String nacion) {
        super(nif, nom, fNac, fAlta); // Inicializa la parte de Cliente
        this.minutosHablados = minutos;
        this.nacionalidad = nacion;
    }

    // Constructor sin fecha de alta (Usa el del padre que pone la fecha por defecto)
    public ClienteTarifaPlana(String nif, String nom, Fecha fNac, float minutos, String nacion) {
        super(nif, nom, fNac);
        this.minutosHablados = minutos;
        this.nacionalidad = nacion;
    }

    // Constructor de copia
    public ClienteTarifaPlana(ClienteTarifaPlana c) {
        super(c); // Copia profunda de fechas y NIF en el padre
        this.minutosHablados = c.minutosHablados;
        this.nacionalidad = c.nacionalidad;
    }

    // --- MÉTODOS ESTÁTICOS (Gestión de oferta) ---

    public static void setTarifa(float limite, float tarifa) {
        ClienteTarifaPlana.limite = limite;
        ClienteTarifaPlana.tarifa = tarifa;
    }
    
    // Getters estáticos pedidos en el main
    public static float getLimite() { return limite; }
    public static float getTarifa() { return tarifa; }

    // --- GETTERS Y SETTERS DE INSTANCIA ---

    public void setMinutos(float minutos) { this.minutosHablados = minutos; }
    public float getMinutos() { return minutosHablados; } // Ojo: en el padre no existe, es propio

    public void setNacionalidad(String nacionalidad) { this.nacionalidad = nacionalidad; }
    public String getNacionalidad() { return nacionalidad; }

    // --- LÓGICA DE NEGOCIO ---

    // Método propio para calcular factura
    public float factura() {
        float exceso = minutosHablados - limite;
        if (exceso < 0) exceso = 0f;
        // 0.15f es el precio fijo del exceso
        return tarifa + (exceso * 0.15f);
    }

    // --- MÉTODOS SOBRESCRITOS ---

  
    public String toString() {
        // Formato salida PDF: ... [300.0 por 20.0] 500.0 --> 50.0
        // super.toString() devuelve la parte de "NIF Fecha: Nombre..."
        return super.toString() + " " + nacionalidad + " [" + limite + " por " + tarifa + "] " + minutosHablados + " --> " + factura();
    }

   
    public Object clone() {
    	// No hace falta try-catch porque Cliente.clone() ya capturó el error.
        // Tampoco hace falta copiar atributos (float y String se copian solos).
        return super.clone();
    }
}
