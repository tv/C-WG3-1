package launch;

import java.io.*;
//import yunikorn.yukon.*;
import yunikorn.yukon.event.SilentYukonPacketObservable;

public class PerformanceTesting {

	public static void main(String[] args) {
		SilentYukonPacketObservable myYukonPacketObservable = new SilentYukonPacketObservable();
		/*myYukonPacketObservable.addListener(new DiscretePacketListener() {

			public void onAudioSequence(AudioSequence sequence) {

				//System.out.println("Framecount: " + sequence.getFramecount());
			}

			public void onVideoFrame(VideoFrame frame) {
				
				
				frame.getBuffer();
				try {
					frame.writeJpg(new File("/home/testi/Desktop/yukon/"
							+ frame.getTimestamp() / 1000 + ".jpg"));
					
				} catch (IOException ex) {
					System.err.println(ex);
				}

			}

		});*/
		PerformanceListener performanceListener = new PerformanceListener();
		myYukonPacketObservable.addListener(performanceListener);
		try {
			myYukonPacketObservable.readStream(new FileInputStream(
					"/home/testi/Desktop/Remote/Old home/yukon.seom"));
			
		} catch (FileNotFoundException ex) {
			System.err.println(ex);
		}
	}
}
