package yunikorn.multipart;



//import java.util.regex.*;
import yunikorn.sink.*;

import com.sun.net.httpserver.*;


public class MJPEGHttpHandler extends ImageHttpHandler {

	public static final String BOUNDARY="yunikorn";
	
	
	//Pattern firefox;
	/*Pattern konqueror;
	Pattern msie;
	Pattern videolan;
	Pattern mplayer;*/
	
	public MJPEGHttpHandler(String virtDir) {
		super(virtDir);
		/*konqueror = Pattern.compile("Mozilla/[45]\\.0 (compatible; Konqueror/.*).*");
		msie = Pattern.compile("Mozilla/[45]\\.0 (compatible; MSIE [4-7]\\.[0-9].*).*");
		videolan = konqueror = Pattern.compile("VLC media player.*");
		mplayer=Pattern.compile("MPlayer.*");*/
	}

	@Override
	protected void setResponseHeaders(Headers headers) {
		// TODO Auto-generated method stub
		headers.set("Content-Type", "multipart/x-mixed-replace;boundary=" + BOUNDARY);
		//headers.set("Content-Type", "image/jpeg;boundary=" + BOUNDARY);
	}

	@Override
	protected void setSingleImageResponseHeaders(Headers headers) {
		// TODO Auto-generated method stub
		headers.set("Content-Type", "image/jpeg");
	}

	@Override
	protected void setHeadlessResponseHeaders(Headers headers) {
		// TODO Auto-generated method stub
		headers.set("Content-Type", "multipart/x-mixed-replace");
	}

	@Override
	protected Streamtype tryStreamtype(Headers headers, Streamtype type) {
		
		
		/*System.out.println("Headers: ");
		for (String t : headers.keySet())
		{
			System.out.println("Header key: " + t + " value: " + headers.get(t));
		}
		System.out.println();*/
		
		
		
		String userAgent = headers.getFirst("User-agent");
		if (userAgent == null){
			return Streamtype.image;
		}
		if (type == Streamtype.image || type == Streamtype.headless)
		{
			return type;
		}
		if (userAgent.contains("Konqueror/") || userAgent.contains("MSIE") || userAgent.contains("Opera") /*|| userAgent.contains("Safari")*/)
		{

				if (headers.get("Referer") == null)
				{
					return type;
				}
				else {
					return Streamtype.image;
				}	
		}
		if (userAgent.contains("VLC media player") || userAgent.contains("MPlayer"))
		{
			return Streamtype.headless;
		}
		
		return type;
		
		
/*		if (msie.matcher(userAgent).matches())
		{
			re
		}*/

		
	}
	
	


	
	

}
