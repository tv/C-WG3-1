package yunikorn.core.chunkstream;
import java.io.*;
/**
 * @author testi
 * 
 * A StreamEvent is an object enclosing data which can be written to an OutputStream.
 * This data often starts and ends at certain points such as start and end of e JPEG file, depending on the type of data  
 * A class implementing this interface must guarantee immutability, because the same object is shared among StreamEventListeners and couldn't be used for some optimizations otherwise.
 *
 */
public interface StreamEvent {
/**
 * This method is used to fetch necessary objects/data from underlying sources such as buffers, files, video frames
 * 
 * 
 * @return true if successfully prepared, otherwise false
 */
public boolean prepare();
/**
 * Writes the enclosed bytes. Calls prepare(), if necessary.
 * 
 * @param out the OutputStream the chunk should be written to, the stream is kept open after writing
 * @throws IOException from operations on OutputStream
 */
public void write(OutputStream out) throws IOException;

}
