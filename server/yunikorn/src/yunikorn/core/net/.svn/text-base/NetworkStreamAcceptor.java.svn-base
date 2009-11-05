package yunikorn.core.net;

import java.net.ServerSocket;
import java.net.Socket;


import yunikorn.core.packet.metainterfaces.PacketObservable;
import yunikorn.core.packet.metainterfaces.PacketObservableFactory;
import yunikorn.core.packet.metainterfaces.PacketStreamListener;
import yunikorn.core.*;
import yunikorn.utils.*;

import java.net.*;
import java.util.*;
import java.io.*;


public class NetworkStreamAcceptor<T extends PacketObservable<?> & StreamParser> {

	private int port;
	private PacketObservableFactory<T> factory;
	private Set<PacketStreamListener<InetAddress, T>> listeners;
        ServerSocket listenSocket;
        
	public NetworkStreamAcceptor(int port,PacketObservableFactory<T> factory) {
		super();
		this.port = port;
		this.factory = factory;
		listeners = new ConcurrentHashSet<PacketStreamListener<InetAddress, T>>();
                listenSocket=null;

	}
	private class ReaderThread implements Runnable
	{
		private StreamParser parser;
		private InputStream stream;

		public ReaderThread(StreamParser parser, InputStream stream) {
			super();
			this.parser = parser;
			this.stream = stream;
		}

		public void run() {
			parser.readStream(stream);
			
		}
		
		
	}
	
        /**
         * Starts listening
         * @throws java.io.IOException when
         */
        public void startListening() throws IOException
	{
		try {
                listenSocket = new ServerSocket(port);
		while (true) {
                        
                        
                        
			Socket clientSocket = listenSocket.accept();
                        
                        
                        
                        
                        
                    
                        
                        
                        System.out.println("Accepting new connection from " + clientSocket.getInetAddress().getHostAddress());
			T observable = factory.createPacketObservable();
			notifyListeners(clientSocket.getInetAddress(), observable);
			new Thread(new ReaderThread(observable, clientSocket.getInputStream())).start();
                        

			
			}
                }/* catch (BindException ex) {
                throw ex;
                }
                catch (ConnectException ex) {
                throw ex;
                }
                catch (NoRouteToHostException ex) {
                throw ex;
                }*/
                catch (SocketException ex) {
                if ( ex.getClass() != SocketException.class) {
                throw ex;
                }
                    
                }
	}
        /**
         * Stops listening (leaving opened connections opened)
         * Does nothing if startListening wasn't called beforehand
         * 
         */
        public void stopListening() throws IOException {
        if (listenSocket != null) {
            
            listenSocket.close();
            
        }
        }
        
	public void addStreamListener(PacketStreamListener<InetAddress, T> listener)
	{
		listeners.add(listener);
	}
	public void removeStreamListener(PacketStreamListener<InetAddress, T> listener)
	{
		listeners.remove(listener);
	}
	private void notifyListeners(InetAddress address, T observable)
	
	{
	for (PacketStreamListener<InetAddress, T> t: listeners)
	{
		t.onIncomingStream(address, observable);
	}
	}
	
	
}
