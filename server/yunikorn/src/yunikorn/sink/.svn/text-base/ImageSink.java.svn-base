package yunikorn.sink;

//import java.awt.image.BufferedImage;
import java.io.*;



//import yunikorn.core.*;
import yunikorn.core.chunkstream.StreamEvent;
import yunikorn.core.chunkstream.StreamEventListener;

abstract public class ImageSink implements StreamEventListener {
    
    public static final int MAX_STREAM_BUFFER=1024*1024*10;

    public void onEndOfStream() {
        close();
    }

    private void close() {
        closed = true;
        try {
            writeEnd(permanentCaster);
            permanentCaster.close();
            headlessCaster.close();
        } catch (IOException ex) {
            System.err.println(this.getClass().getSimpleName() + ": " + ex);
        }


    }

    private void flush() {
        try {
            permanentCaster.flush();
            headlessCaster.flush();
        } catch (IOException ex) {
            System.err.println(this.getClass().getSimpleName() + ": " + ex);
        }
    }
    DynamicOutputStreamMulticaster permanentCaster;
    DynamicOutputStreamMulticaster oneTimeCaster;
    DynamicOutputStreamMulticaster headlessCaster;
    //PacketObservable<?,?> observable;
    byte[] lastImage;
    StreamEvent unconvertedLastEvent; //We hold this one in case there is no listener during the stream, but in case we want to provide an after-stream image that is only converted to the image format in case there is someone requesting the image
    boolean closed;

    public ImageSink() {
        super();
        permanentCaster = new DynamicOutputStreamMulticaster(true, MAX_STREAM_BUFFER);
        oneTimeCaster = new DynamicOutputStreamMulticaster(true);
        headlessCaster = new DynamicOutputStreamMulticaster(true, MAX_STREAM_BUFFER);
        lastImage = null;
        unconvertedLastEvent = null;
        closed = false;

    }

    /*public void onAudioSequence(AudioSequence sequence) {
    // TODO Auto-generated method stub
    }*/
    public void onStreamEvent(StreamEvent event) {
        //lastEvent = event;
        if (permanentCaster.isEmpty() && oneTimeCaster.isEmpty() && headlessCaster.isEmpty()) {
            unconvertedLastEvent = event;
            return;
        }
        //BufferedImage image;
		/*if (frame instanceof SilentYukonVideoFrame){ //This is a workaround because ImageIO fails.
        image = ((SilentYukonVideoFrame)frame).getCompatibleBufferedImage();
        } else {
        image = frame.getBufferedImage();	
        }*/

        /*image = frame.getBufferedImage();
        if (image == null){return;}*/
        synchronized (event) {
            if (!event.prepare()) {
                return;
            }
        }


        try {
            permanentCaster.queueObservers();



            writeFrameStart(permanentCaster);

            headlessCaster.queueObservers();


            oneTimeCaster.queueObservers();
            DynamicOutputStreamMulticaster temp = new DynamicOutputStreamMulticaster(); //We could also us a "lighter" object
            temp.addStream(permanentCaster);
            temp.addStream(headlessCaster);
            temp.addStream(oneTimeCaster);

            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            temp.addStream(bos);


            event.write(temp);
            lastImage = bos.toByteArray();
            unconvertedLastEvent = null; //As of NOW - the most current image holder is lastImage and not unconvertedLastEvent
            //writeImage(image, temp);


            oneTimeCaster.close(false);
            oneTimeCaster.flushObservers();



            flush(); //necessary? Yes, absolutely necessary! You're going to have low "fps" inside the viewer otherwise, because frames are sent together at random time. Besides it avoids ChunkedOutputStream to throw IndexOutOfBoundsExceptions.

            headlessCaster.flushObservers();

            writeFrameEnd(permanentCaster);



            permanentCaster.flushObservers();

        } catch (IOException ex) {
            close();
            System.err.println(ex);
        }


    }

    public void addStream(OutputStream stream) throws IOException {
        writeIntro(stream);
        permanentCaster.addStream(stream);
    }

    public void addSingleImageStream(OutputStream stream) {
        oneTimeCaster.addStream(stream);
    }

    /**
     * Immediately writes the last received image and closes the stream - or only closes the stream immediately if no image was received yet
     * @param stream to write to
     * @throws java.io.IOException for failed operations on stream
     */
    public void writeLastImage(OutputStream stream) throws IOException {


        synchronized (this) {
        if (unconvertedLastEvent != null) { //The question we ask here is: Who holds the most current picture (Is it unconvertedLastEvent?). The question isn't answered totally dependable and it does not matter.
            ByteArrayOutputStream bstream = new ByteArrayOutputStream();

            unconvertedLastEvent.write(bstream);
            lastImage = bstream.toByteArray();
            unconvertedLastEvent = null;

            

        }
        }
        
        if (lastImage != null) {
            stream.write(lastImage);
        }

        
        stream.close();

    }

    public void addHeadlessStream(OutputStream stream) {
        headlessCaster.addStream(stream);
    }

    public int streamListenerCount() {
        return permanentCaster.count() + headlessCaster.count();
    }

    public boolean isClosed() {
        return closed;
    }

    abstract protected void writeEnd(OutputStream ostream) throws IOException;
    //abstract protected void writeImage(BufferedImage image, OutputStream ostream) throws IOException;
    abstract protected void writeIntro(OutputStream stream) throws IOException;

    abstract protected void writeFrameStart(OutputStream stream) throws IOException;

    abstract protected void writeFrameEnd(OutputStream stream) throws IOException;
}
