package launch;
import java.net.*;
import java.io.*;
import java.awt.image.*;
import java.awt.event.*;

import javax.swing.*;
import java.awt.*;
//import yunikorn.yukon.*;
import yunikorn.yukon.event.YukonPacketObservable;
//import yunikorn.core.*;
import yunikorn.core.packet.AudioSequence;
import yunikorn.core.packet.DefaultMediaStreamListener;
import yunikorn.core.packet.VideoFrame;
public class YukonDisplay {
public static void main(String[] args)
{
	try {


	
	YukonPacketObservable observable = new YukonPacketObservable();
	Canvas canvas = new Canvas();
	observable.addListener(canvas);

	
	ServerSocket listenSocket = new ServerSocket(42803);
	while (!canvas.closed()) {
	Socket clientSocket = listenSocket.accept();
	InputStream yukonStream = clientSocket.getInputStream();
	
	observable.readStream(yukonStream);
	}
	//observable.readStream(new FileInputStream("/home/testi/Desktop/Remote/Old home/yukon.seom"));
	} catch (IOException ex)
	{
		System.err.println(ex);
	}




}
public static class Canvas extends JFrame implements DefaultMediaStreamListener, WindowListener
{
public void windowActivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	public void windowClosed(WindowEvent e) {
		closed=true;
	}

	public void windowClosing(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	public void windowDeactivated(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	public void windowDeiconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	public void windowIconified(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}

	public void windowOpened(WindowEvent e) {
		// TODO Auto-generated method stub
		
	}
static final long serialVersionUID=1;

BufferedImage currentImage;
boolean started;
boolean closed;
public boolean closed()
{
return closed;
}

public Canvas()
{
started=false;
closed=false;
currentImage=null;
this.addWindowListener(this);
}


	public void onAudioSequence(AudioSequence sequence) {

		
	}

	public void onVideoFrame(VideoFrame frame) {
		if (!started)
		{
			//this.setSize(frame.getWidth(),frame.getHeight());
			this.setVisible(true);
			started=true;
		
		}
		this.setSize(frame.getWidth(),frame.getHeight());
		try {
                currentImage=frame.getBufferedImage();
                } catch (IOException ex) {
                System.err.println(ex);
                
		this.repaint();
                }
		
		
	}
	public void paint(Graphics g)
	{
		
		if (currentImage!=null)
		{
			g.drawImage(currentImage, 0,0,null);
		} else {
			super.paint(g);
		}
	}

	public void onEndOfStream() {
		
	}

}
	
}
