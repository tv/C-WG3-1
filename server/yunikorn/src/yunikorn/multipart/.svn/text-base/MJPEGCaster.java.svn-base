package yunikorn.multipart;



import java.io.IOException;

//import yunikorn.core.net.NetworkStreamAcceptor;
//import yunikorn.core.packet.AudioSequence;
//import yunikorn.core.packet.StreamDataPacketListener;
//import yunikorn.core.packet.StreamDataPacketObservable;
import yunikorn.core.packet.*;
import yunikorn.sink.*;

public class MJPEGCaster<T extends VideoFrame,E extends AudioSequence> extends ImageCaster<T,E> {




	public MJPEGCaster(
			int httpPort)
			throws IOException {
		super(httpPort);
		// TODO Auto-generated constructor stub
	}

	public MJPEGCaster()
			throws IOException {
		super();
		// TODO Auto-generated constructor stub
	}

	protected ImageHttpHandler instantiateHandler(String virtDir) {
		// TODO Auto-generated method stub
		return new MJPEGHttpHandler(virtDir);
	}
	
	@Override
	protected ImageSink instantiateSink() {
		// TODO Auto-generated method stub
		return new MJPEGSink();
	}

	@Override
	protected PacketProxyStreamObservable instantiateProxy() {
		// TODO Auto-generated method stub
		return new JPEGProxy();
	}


	
}
