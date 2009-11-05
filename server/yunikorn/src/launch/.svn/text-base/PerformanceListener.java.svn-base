package launch;


import yunikorn.core.packet.AudioSequence;
import yunikorn.core.packet.*;
import java.io.*;

//import javax.imageio.*;

public class PerformanceListener implements DefaultMediaStreamListener {

	long totalTime;
	int frameCount;
	
	public PerformanceListener() {
		super();
		totalTime = 0;
		frameCount=0;
	}

	public void onAudioSequence(AudioSequence sequence) {


	}

	public void onVideoFrame(VideoFrame frame) {
		long start = System.nanoTime();
		//frame.getBufferedImage();
		//frame.getCompatibleBufferedImage();
                try {
		frame.getBufferedImage();
                } catch (IOException ex) {
                System.err.print(ex);
                }
		
		totalTime+=System.nanoTime()-start;
		frameCount++;

	}

	public long getTotalTime() {
		return totalTime;
	}

	public int getFrameCount() {
		return frameCount;
	}
	public long getAverageFrameTime()
	{
		return totalTime/frameCount;
	}

	public void onEndOfStream() {
		System.out.println("Totaltime: " + getTotalTime() + " Milliseconds: " + getTotalTime()/1000000);
		System.out.println("Average time per frame: " + getAverageFrameTime() + " Milliseconds: " + getAverageFrameTime()/1000000);
		System.out.println("Framecount: " + getFrameCount());
	}

}
