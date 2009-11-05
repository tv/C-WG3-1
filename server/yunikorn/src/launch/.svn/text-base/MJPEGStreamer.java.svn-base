package launch;
import java.io.*;

import yunikorn.multipart.*;
import yunikorn.core.net.*;
import yunikorn.yukon.*;
import yunikorn.yukon.factory.*;;




public class MJPEGStreamer {
    
        public static MediaStreamAcceptor<SilentYukonVideoFrame, SilentYukonAudioSequence> acceptor=null;
	public static void main(String[] args)
	{
            try {
                        Runtime.getRuntime().addShutdownHook(new Thread() {
                        public void run() {
                        if (acceptor != null) {
                            try {
                            System.out.println("Shutdown");
                            acceptor.stopListening();

                            } catch (IOException ex) {
                            System.err.println(ex);
                            }
                        }
                        }
                        });
            }
                        catch (IllegalStateException ex) {
                        //Don't care if already shutting down
                        }
            
            
            
		int yukonPort=42803;
		int httpPort=3022;
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
			System.out.println("Starting Yunikorn Multipart-JPEG-Streaming-Server on port " + httpPort + ", accepting yukon/seom streams on port " + yukonPort);
			acceptor = new MediaStreamAcceptor<SilentYukonVideoFrame,SilentYukonAudioSequence>(yukonPort, new SilentYukonPacketObservableFactory());
			
			MJPEGCaster<SilentYukonVideoFrame, SilentYukonAudioSequence> myCaster = new MJPEGCaster<SilentYukonVideoFrame, SilentYukonAudioSequence>(httpPort);
			acceptor.addStreamListener(myCaster);

                        acceptor.startListening();
			
		} catch (IOException ex)
		{
			System.err.println("Failed to setup server: " + ex);
                        System.exit(0);
			//ex.printStackTrace();
		}

		
		
	}
	
}
