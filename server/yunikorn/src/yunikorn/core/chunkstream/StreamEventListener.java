package yunikorn.core.chunkstream;
import yunikorn.core.*;
public interface StreamEventListener extends StreamListener {
public void onStreamEvent(StreamEvent event);

}
