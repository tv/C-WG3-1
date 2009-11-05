package yunikorn.yukon.http;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;

import com.sun.net.httpserver.HttpServer;

import yunikorn.core.StreamListener;

import yunikorn.core.packet.metainterfaces.*;

//import yunikorn.sink.ImageSink;

import yunikorn.yukon.*;

import yunikorn.yukon.event.*;

public class YukonRecaster implements PacketStreamListener<InetAddress, CompressedPacketStreamObservable> {

	public void onIncomingStream(InetAddress sourceDescription,
			CompressedPacketStreamObservable packetObservable) {

		
		

		
		//YukonSink sink = new YukonSink();
		YukonStreamRepeater repeater = new YukonStreamRepeater();

		packetObservable.addListener(repeater);
		
		//packetObservable.addStreamListener(handler);
		String newIdentifier = handler.addCast(sourceDescription.getHostName(),  repeater);
		
		packetObservable.addStreamListener(new RemoveListener(newIdentifier));
	}
	
	
	
	
	
	
	private class RemoveListener implements StreamListener
	{
	String identifier;

	public RemoveListener(String identifier) {
		super();
		this.identifier = identifier;
	}

	public void onEndOfStream() {
	handler.removeCast(identifier);
		
	}

	}


		

		
		
			
			String virtDir;
			YukonHttpRepeater handler;
			
			
		public YukonRecaster(int httpPort) throws IOException {
			super();
			
			
			
			virtDir = "/stream";
			handler = new YukonHttpRepeater(virtDir);
			HttpServer server = HttpServer.create(new InetSocketAddress(httpPort),20);
			server.createContext(virtDir,handler);
			server.start();	

		}
	
	
	
	
	
	
	
	
	
	
	
	
	

}
