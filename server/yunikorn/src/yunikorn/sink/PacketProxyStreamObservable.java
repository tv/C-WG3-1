package yunikorn.sink;
//import yunikorn.core.*;
import yunikorn.core.chunkstream.StreamEventObservable;
import yunikorn.core.packet.DefaultMediaStreamListener;
/**
 * @author testi
 * 
 * classes implementing this interface transform either VideoFrame or AudioSequence objects to chunks writable to an OutputStream of the Listener by instantiating an object of type StreamEvent enclosing that data 
 *
 */
public interface PacketProxyStreamObservable extends DefaultMediaStreamListener, StreamEventObservable {

}
