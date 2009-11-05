package yunikorn.sink;

import java.io.FilterOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.*;

public class ThreadedOutputStream extends FilterOutputStream {
    
int byteBuffer;
Object byteBufferLock;
int maxBufferSize;


//private static final String BUFFER_LIMIT_EXCEED="Buffer limit exceeded";

	private class WriterThread implements Runnable {

		public void run()
		{
			try {
			while(open && !excepted) {
				OutputStreamCommand command = null;
				synchronized(buffers)
				{
					if (buffers.isEmpty()) {
						buffers.wait();
					}
					command = buffers.poll();
				
				if (command == null){excepted=true;buffers.clear();return;} //In most cases it doesn't matter if you clear buffers, because I/O-Streams throwing exceptions are usually disbanded -> garbage collected
                                
                                }
                                try {
				command.execute();
				}catch(RuntimeException ex){
					System.err.println("Workaround catch: " + ex);
					excepted=true;
				}
			}
			} catch (InterruptedException ex){
				excepted=true;
			}
		}

	}

	
	private interface OutputStreamCommand
	{
		public void execute();
	}
	private class CloseCommand implements OutputStreamCommand
	{

		public void execute() {
			try {
			out.close();
			}catch(IOException ex)
			{excepted=true;}
		}
		
	}
	private class FlushCommand implements OutputStreamCommand
	{

		public void execute() {
			try {
			out.flush();
			}catch(IOException ex)
			{excepted=true;}
		}
		
	}
	private class WriteByteCommand implements OutputStreamCommand
	{
		
		int write;
		public WriteByteCommand(int b)
		{
		write = b;
		}
		public void execute() {
			try {
			out.write(write);
                        if (maxBufferSize != Integer.MAX_VALUE) {
                        synchronized (byteBufferLock) {
                        byteBuffer--;
                        }
                        }
			}catch(IOException ex)
			{excepted=true;}
		}
		
	}
	private class WriteByteArrayCommand implements OutputStreamCommand
	{
		
		byte[] write;
		public WriteByteArrayCommand(byte[] array)
		{
		write = array;
		}
		public void execute() {
			try {
			out.write(write);
                        if (maxBufferSize != Integer.MAX_VALUE) {
                        synchronized (byteBufferLock) {
                        byteBuffer-=write.length;
                        }
                        }
                        
			}catch(IOException ex)
			{excepted=true;}
		}
		
	}
	private class WriteOffsetByteArrayCommand implements OutputStreamCommand
	{
		
		byte[] write;
		int offset;
		int length;
		public WriteOffsetByteArrayCommand(byte[] array, int offset, int length)
		{
		write = array;
		this.offset=offset;
		this.length=length;;
		}
		public void execute() {
			try {
			out.write(write,offset,length);
                        if (maxBufferSize != Integer.MAX_VALUE) {
                        synchronized (byteBufferLock) {
                        byteBuffer-=length;
                        }
                        }
                        
			}catch(IOException ex)
			{excepted=true;}
		}
		
	}

	LinkedList<OutputStreamCommand> buffers;
	private boolean open;
	private boolean excepted;
	private boolean started;
	//private OutputStream out;
	//WriterThread writer;

	public ThreadedOutputStream(OutputStream out, boolean standalone, int maxBufferSize) {
		super(out);
		buffers = new LinkedList<OutputStreamCommand>();
		excepted = false;
		open=true;
		started=standalone;
                byteBufferLock = new Object();
                byteBuffer = 0;
                this.maxBufferSize=maxBufferSize;
		if (standalone) {
		new Thread(new WriterThread()).start();
		}
	}
        public ThreadedOutputStream(OutputStream out, boolean standalone) {
        this(out,standalone,Integer.MAX_VALUE);
        }
	public void start()
	{
		if (started){return;}
		started=true;
		new WriterThread().run();
	}

	@Override
	public void close() throws IOException {
		// TODO Auto-generated method stub
		process(new CloseCommand());
		
	}

	@Override
	public void flush() throws IOException {
		// TODO Auto-generated method stub
		process(new FlushCommand());
	}

	@Override
	public void write(byte[] b, int off, int len) throws IOException {
		/*byte[] newb = new byte[len];
		System.arraycopy(b, off, newb, 0, len);*/
            if (maxBufferSize != Integer.MAX_VALUE) {
            synchronized(byteBufferLock) {
            byteBuffer+=len;
            checkBuffer();
            
            }
            }
            
		process(new WriteOffsetByteArrayCommand(b,off,len));
	}

	@Override
	public void write(byte[] b) throws IOException {
		/*byte[] newb = new byte[b.length];
		System.arraycopy(b, 0, newb, 0, b.length);*/
            if (maxBufferSize != Integer.MAX_VALUE) {
            synchronized(byteBufferLock) {
            byteBuffer+=b.length;
            checkBuffer();
            
            }
            }
		process(new WriteByteArrayCommand(b));
	}

	@Override
	public void write(int b) throws IOException {
            if (maxBufferSize != Integer.MAX_VALUE) {
            synchronized(byteBufferLock) {
            byteBuffer++;
            checkBuffer();
            }
            }
            process(new WriteByteCommand(b));

	}
        
	private void process(OutputStreamCommand command) throws IOException
	{
		if (excepted){throw new IOException();}
		synchronized (buffers) {
			buffers.add(command);
			buffers.notify();
		}
	}
        
        private void checkBuffer() throws IOException {
        
            if (byteBuffer>maxBufferSize) {
                //System.err.println("Check: " + byteBuffer + " > " + maxBufferSize);
                throw new IOException("Buffer limit exceeded");}
        }

}
