package yunikorn.sink;

import java.io.*;
import java.util.*;

public class DynamicOutputStreamMulticaster extends OutputStream {

	Set<OutputStream> observers;
	List<OutputStream> waitQueue;
	boolean queue;
	boolean closed;
	boolean threaded;
        int maxBufferSize;
	public DynamicOutputStreamMulticaster(boolean threaded, int maxBufferSize) {
		super();
		observers = new HashSet<OutputStream>();
		waitQueue = new LinkedList<OutputStream>();
		queue = false;
		this.threaded=threaded;
                this.maxBufferSize=maxBufferSize;
		closed=false;
	}
        public DynamicOutputStreamMulticaster(boolean threaded) {
        this(threaded,Integer.MAX_VALUE);
        }
        
	public DynamicOutputStreamMulticaster()
	{
		this(false);
	}

	public void queueObservers() {
		queue = true;
	}

	public void flushObservers() {
		queue = false;
		synchronized (observers)
		{
			synchronized (waitQueue)
			{
				observers.addAll(waitQueue);
				waitQueue.clear();
			}
		}
	}

	@Override
	public void write(int b) {
		synchronized (observers) {
			List<OutputStream> problematic = new LinkedList<OutputStream>();
			for (OutputStream t : observers) {
				try {
					t.write(b);
				} catch (IOException ex) {
					problematic.add(t);
					System.err.println(this.getClass().getSimpleName() + ": " + ex);
				}
				/*catch (RuntimeException ex)
				{
					problematic.add(t);
					System.err.println("Multiplexer write - Workaround catch: " + ex);
				}*/
			}
			for (OutputStream t : problematic)
			{
				observers.remove(t);
			}
			
		}

	}
	public void clear()
	{
		synchronized(observers)
		{
			observers.clear();
		}
	}
        
	public void close(boolean finalClose) {
		synchronized (observers) {
                    if (!closed) {
                    closed=finalClose;}
			for (OutputStream t : observers) {
				try {
					t.close();
				} catch (IOException ex) {
					System.err.println(this.getClass().getSimpleName() + ": " + ex);
				}
				/*catch (RuntimeException ex) {
				System.err.println("Multiplexer close - Workaround catch: " + ex);
				}*/
			}
			observers.clear();
		}
	}
        @Override
        public void close()
        {
        close(true);
        }

	public void reopen()
	{
		closed=false;
	}
	
	
	
	@Override
	public void flush() throws IOException {
		synchronized (observers) {
			List<OutputStream> problematic = new LinkedList<OutputStream>();
			for (OutputStream t : observers) {
				try {
					t.flush();
				} catch (IOException ex) {
					problematic.add(t);
					System.err.println(this.getClass().getSimpleName() + ": " + ex);
				}
				/*catch (RuntimeException ex)
				{
					problematic.add(t);
					System.err.println("Multiplexer write - Workaround catch: " + ex);
				}*/
			}
			for (OutputStream t : problematic)
			{
				observers.remove(t);
			}
			
		}

	}
	
	
	

	public void addStream(OutputStream stream) {
		OutputStream e;
		if (threaded)
		{
			e = new ThreadedOutputStream(stream,true,maxBufferSize);
		} else {
			e = stream;
		}
		
		if (!queue) {
			synchronized (observers) {
				if (closed) {
					try {
					stream.close();
					return;
					} catch (IOException ex){System.err.println(this.getClass().getSimpleName() + ": " + ex);}
				}
			observers.add(e);
			}
		} else
		{
			synchronized (waitQueue) { //!
			waitQueue.add(e);
			}
		}
	}

	/*private void remove(Object o) {

		synchronized (observers) {
		if (!observers.remove(o)) {
			synchronized (waitQueue) {
			waitQueue.remove(o);
			}
		}
	}
	}*/
	public boolean isEmpty()
	{
		synchronized (observers) {
			return observers.isEmpty();
		}
	}

	@Override
	public void write(byte[] b, int off, int len) throws IOException {
		// TODO Auto-generated method stub
		//Optimization-Override
		byte[] newb;
		int newoff;
		synchronized (observers) {
		if (threaded && observers.size() > 0) {
		newb = new byte[len];
		System.arraycopy(b, off, newb, 0, len); //Required because byte array isn't immutable and could be changed if ThreadedOutputStream is used (alternate is to use CopyThreadedOutputStream, which would cause more arraycopy calls if there is more than one OutputStream)
		newoff = 0;
		} else {
			newb = b;
			newoff = off;
		}

			
				List<OutputStream> problematic = new LinkedList<OutputStream>();
				for (OutputStream t : observers) {
					try {
						t.write(newb,newoff,len);
					} catch (IOException ex) {
						problematic.add(t);
						System.err.println(this.getClass().getSimpleName() + ": " + ex);
					}
					/*catch (RuntimeException ex)
					{
						problematic.add(t);
						System.err.println("Multiplexer write - Workaround catch: " + ex);
					}*/
				}
				for (OutputStream t : problematic)
				{
					observers.remove(t);
				}
				
			}

		
		
		
		
	}

	@Override
	public void write(byte[] b) throws IOException {
		// TODO Auto-generated method stub
		write(b,0,b.length);
	}
	public int count()
	{
		return observers.size() + waitQueue.size();
	}
	
	

}
