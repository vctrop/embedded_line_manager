/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Serial;
import gerenciador.de.filas.Gereciador_de_filas;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;
import jdk.nashorn.internal.objects.NativeArray;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author Igor
 */
public class SerialRxTx implements SerialPortEventListener{
SerialPort serialPort=null;
    
private Protocolo protocolo =new Protocolo();
private String appName;// nome aplicacao

private BufferedReader input;
private OutputStream output;

private static final int TIME_OUT =1000; // tempo de espera
private static  int DATA_RATE =9600;

private String serialPortName ="COM8";

public ArrayList<String> Lista_Portas(){
    
    ArrayList<String> portas = new ArrayList<String> ();
            
    try{
        CommPortIdentifier portid = null;
        Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();
      
        while( portEnum.hasMoreElements()){
            CommPortIdentifier currPortId=(CommPortIdentifier) portEnum.nextElement();
           //System.out.println( currPortId.getName().toString());
            portas.add(currPortId.getName().toString());
          
        }
            
        }catch(Exception e){
                
         }
    return portas;
    
}
public String iniciaSerial(String com){
    serialPortName=com;
    boolean status=false;
    String conect="desconectado";
    try{
        CommPortIdentifier portid = null;
        Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();
        
        while(portid ==null && portEnum.hasMoreElements()){
            CommPortIdentifier currPortId=(CommPortIdentifier) portEnum.nextElement();
            if(currPortId.getName().equals(getSerialPortName())){
                serialPort=(SerialPort) currPortId.open(appName, TIME_OUT);
                portid=currPortId;
                conect="Conectado em: " + currPortId.getName();
                System.out.println(conect);
                break;
                
            }
            
        }
        if(portid==null || serialPort==null){
            return "desconectado";
        }
        
        serialPort.setSerialPortParams(getDATA_RATE(), serialPort.DATABITS_8,
                serialPort.STOPBITS_1,
                serialPort.PARITY_NONE);
        
        serialPort.addEventListener(this);
        serialPort.notifyOnDataAvailable(true);
        status=true;
        
        try{
            Thread.sleep(1000);
            
        }catch(InterruptedException e){
            e.printStackTrace();
            
        }
        
        return conect;
        
    }catch(Exception e){
        e.printStackTrace();
        status=false;
    }
    
    return conect;
}

    public void sendData ( String  data){
        try{
            output= serialPort.getOutputStream();
            output.write(data.getBytes());
                        
        }catch(Exception e){
            System.err.println(e.toString());
            
        }
        
    }
    
    
    
    
    public synchronized String close(){
        if(serialPort!=null){
            serialPort.removeEventListener();
            serialPort.close();
            return "Desconectado";
        }
    return "falha ao desconectar";
    }

    @Override
    public void serialEvent(SerialPortEvent spe) {
     //   throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        
        try{
            switch(spe.getEventType()){
                case SerialPortEvent.DATA_AVAILABLE:
                    
                    if(input==null){
                        input=new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
                        
                    }
                    
                    //char inputchar =(char) input.read();
                    String inputLine =input.readLine(); // enivo dados tem que ter\r no final
                    //System.out.println("chegou dados");
                    txtreceber(inputLine);
                    //System.out.println(inputchar);
                    //char inputchar =(char) input.read();
                    //System.out.println(inputchar);
                 //System.out.println("chegou : " + inputLine);
                    //getProtocolo().setLeituracomando(input.readLine());
                   // System.out.println("chegou : " + getProtocolo().getLeituracomando());
                    
                    break;
                 default:
                     break;
                
            }
        }catch(Exception e){
         System.err.println(e.toString());
        }
    }

    /**
     * @return the protocolo
     */
    public Protocolo getProtocolo() {
        return protocolo;
    }

    /**
     * @param protocolo the protocolo to set
     */
    public void setProtocolo(Protocolo protocolo) {
        this.protocolo = protocolo;
    }

    /**
     * @return the DATA_RATE
     */
    public static int getDATA_RATE() {
        return DATA_RATE;
    }

    /**
     * @param aDATA_RATE the DATA_RATE to set
     */
    public static void setDATA_RATE(int aDATA_RATE) {
        DATA_RATE = aDATA_RATE;
    }

    /**
     * @return the serialPortName
     */
    public String getSerialPortName() {
        return serialPortName;
    }

    /**
     * @param serialPortName the serialPortName to set
     */
    public void setSerialPortName(String serialPortName) {
        this.serialPortName = serialPortName;
    }
    
    public void txtreceber(String data){
        
        Gereciador_de_filas.textoexterno=data;
        Gereciador_de_filas.textoexternoAv=1;
        //System.out.println(data);
        
    }
    
}
