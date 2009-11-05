package yunikorn.sink;
import com.sun.net.httpserver.*;
import java.net.*;
import java.io.*;
//import yunikorn.core.net.*;
import yunikorn.core.packet.*;
import yunikorn.core.packet.metainterfaces.PacketStreamListener;
import yunikorn.core.*;



abstract public class ImageCaster<T extends VideoFrame,E extends AudioSequence> implements PacketStreamListener<InetAddress, MediaStreamObservable<T,E>> {
	int httpPort;

/*private class RemoveListener implements StreamListener
{
String identifier;

public RemoveListener(String identifier) {
	super();
	this.identifier = identifier;
}

public void onEndOfStream() {
handler.removeCast(identifier);
	
}

}*/
	public void onIncomingStream(
			InetAddress sourceDescription,
			MediaStreamObservable<T,E> packetObservable) {
			
			


			
			ImageSink sink = instantiateSink();
			PacketProxyStreamObservable proxy = instantiateProxy();
			packetObservable.addListener(proxy);
			proxy.addStreamEventListener(sink);
			
			//packetObservable.addStreamListener(handler);
			String newIdentifier = handler.addCast(sourceDescription.getHostName(),  sink);
			
			//packetObservable.addStreamListener(new RemoveListener(newIdentifier));
			

						
			
		}

	

	
	
		
		String virtDir;
		ImageHttpHandler handler;
		
		
	public ImageCaster(int httpPort) throws IOException {
		super();
		this.httpPort = httpPort;
		
		
		
		virtDir = "/";
		handler = instantiateHandler(virtDir);
		HttpServer server = HttpServer.create(new InetSocketAddress(httpPort),20);
		server.createContext(virtDir,handler);
		server.start();	

	}
	public ImageCaster() throws IOException
	{
		this(3022);
	}

	abstract protected ImageSink instantiateSink();
	abstract protected ImageHttpHandler instantiateHandler(String virtDir);
	abstract protected PacketProxyStreamObservable instantiateProxy();
	
	public ImageHttpHandler getHandler() {
		return handler;
	}

	
	
	
	
	
}
