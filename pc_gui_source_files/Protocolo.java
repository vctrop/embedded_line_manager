/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Serial;

/**
 *
 * @author Igor
 */
public class Protocolo {

    /**
     * @return the tipoDado
     */
    public String getTipoDado() {
        return tipoDado;
    }

    /**
     * @param tipoDado the tipoDado to set
     */
    public void setTipoDado(String tipoDado) {
        this.tipoDado = tipoDado;
    }

    /**
     * @return the temperatura
     */
    public String getTemperatura() {
        return temperatura;
    }

    /**
     * @param temperatura the temperatura to set
     */
    public void setTemperatura(String temperatura) {
        this.temperatura = temperatura;
    }

    /**
     * @return the umidade
     */
    public String getUmidade() {
        return umidade;
    }

    /**
     * @param umidade the umidade to set
     */
    public void setUmidade(String umidade) {
        this.umidade = umidade;
    }

    /**
     * @return the distancia
     */
    public String getDistancia() {
        return distancia;
    }

    /**
     * @param distancia the distancia to set
     */
    public void setDistancia(String distancia) {
        this.distancia = distancia;
    }

    /**
     * @return the luminosidade
     */
    public String getLuminosidade() {
        return luminosidade;
    }

    /**
     * @param luminosidade the luminosidade to set
     */
    public void setLuminosidade(String luminosidade) {
        this.luminosidade = luminosidade;
    }

    /**
     * @return the led
     */
    public String getLed() {
        return led;
    }

    /**
     * @param led the led to set
     */
    public void setLed(String led) {
        this.led = led;
    }

    /**
     * @return the botao
     */
    public String getBotao() {
        return botao;
    }

    /**
     * @param botao the botao to set
     */
    public void setBotao(String botao) {
        this.botao = botao;
    }

    /**
     * @return the potenciometro
     */
    public String getPotenciometro() {
        return potenciometro;
    }

    /**
     * @param potenciometro the potenciometro to set
     */
    public void setPotenciometro(String potenciometro) {
        this.potenciometro = potenciometro;
    }

    /**
     * @return the leituracomando
     */
    public String getLeituracomando() {
        return leituracomando;
    }

    /**
     * @param leituracomando the leituracomando to set
     */
    public void setLeituracomando(String leituracomando) {
        this.leituracomando = leituracomando;
        this.interpretaComando();// interpretamos a string
        
    }
    private String tipoDado;
    private String temperatura;
    private String umidade;
    private String distancia;
    private String luminosidade;
    private String led;
    private String botao;
    private String potenciometro;
    
    private String leituracomando;
    
    private void interpretaComando(){
        String aux[]=leituracomando.split(",");
        
        if(aux.length==8){
        
            tipoDado =aux[0];
            temperatura=aux[1];
            umidade=aux[2];
            distancia=aux[3];
            luminosidade=aux[4];
            led=aux[5];
            botao=aux[6];
            potenciometro=aux[7];
        
        }
        
    }
}
