package launch;
//import yunikorn.core.packet.*;
import yunikorn.core.net.*;
//import yunikorn.core.packet.metainterfaces.*;
import yunikorn.yukon.event.*;

import yunikorn.yukon.http.*;
import yunikorn.yukon.factory.*;
import java.io.*;
public class HttpRepeater {
	public static void main(String[] args)
	{
		int yukonPort=42803;
		int httpPort=3023;
		if (args.length>0){
			try {
				httpPort=Integer.parseInt(args[0]);
			}
			catch (NumberFormatException ex){}
		
		if (args.length>1){
			try {
				yukonPort=Integer.parseInt(args[1]);
			}
			catch (NumberFormatException ex){}
			
		}
		}	
		
		try {
			System.out.println("Yukon Http Stream Repeater on port " + httpPort + ", accepting yukon/seom streams on port " + yukonPort);
			NetworkStreamAcceptor<CompressedPacketStreamObservable> acceptor = new NetworkStreamAcceptor<CompressedPacketStreamObservable>(yukonPort, new CompressedPacketStreamObservableFactory());
			
			YukonRecaster myCaster = new YukonRecaster(httpPort);
			acceptor.addStreamListener(myCaster);
			acceptor.startListening();
			
		} catch (IOException ex)
		{
			System.err.println("Failed to setup server: " + ex);
			//ex.printStackTrace();
		}

		
		
	}
}
