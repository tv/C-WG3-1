package yunikorn.sink;
//import java.io.IOException;
//import yunikorn.core.*;
import java.io.*;
import java.util.*;
import java.net.*;

import com.sun.net.httpserver.*;


abstract public class ImageHttpHandler implements HttpHandler {

	
	public enum Streamtype
	{
		forcedstream,
		forcedimage,
		forcedheadless,
		stream,
		image,
		headless
	}
	//DynamicOutputStreamMultiplexer dynamicMultiplexer;
	final Map<String, ImageSink> casts;

	String virtDir;
	public ImageHttpHandler(String virtDir) {
		super();
		if (!virtDir.startsWith("/")) {throw new IllegalArgumentException("context string must start with /");}
        while (!virtDir.isEmpty() && virtDir.charAt(virtDir.length()-1) == '/') {
        virtDir = virtDir.substring(0,virtDir.length()-1);
        }
        this.virtDir = virtDir;
		//this.dynamicMultiplexer = dynamicMultiplexer;
		casts = new HashMap<String, ImageSink>(); 
	}

	public void handle(HttpExchange exchange) throws IOException {
		
		InputStream requestBody = exchange.getRequestBody();
		
		
		while(requestBody.read()!=-1)
		{
		}
		
		/*System.out.println("Headers - " + exchange.getRemoteAddress().getAddress().getHostAddress());
		Headers rheaders = exchange.getRequestHeaders();
		for (String t : exchange.getRequestHeaders().keySet())
		{
			System.out.println("Header key: " + t + " value: " + rheaders.get(t));
		}
		System.out.println();*/
		
		URI uri = exchange.getRequestURI();
		StringTokenizer pathTokens = new StringTokenizer(uri.getPath().substring(virtDir.length()),"/");
		/*if (!pathTokens.hasMoreTokens()) {
			exchange.sendResponseHeaders(404,0);
			Headers headers = exchange.getResponseHeaders();
			headers.set("Content-Type", "text/html");
			exchange.getResponseBody().write("Not found".getBytes());
			exchange.getResponseBody().close();
			return;
		}*/
		//pathTokens.nextToken();
		if (!pathTokens.hasMoreTokens())
		{
			listStreams(exchange);
			return;
		}
		//try {
			
		String streamID = pathTokens.nextToken();
		ImageSink cast=null;
		synchronized (casts) {
		cast = casts.get(streamID);
		}
                if (cast == null)
		{
			Headers headers = exchange.getResponseHeaders();
			headers.set("Content-Type", "text/html");
			exchange.sendResponseHeaders(404,0);
			exchange.getResponseBody().write("<html><head><title>Error</title></head><body>Stream not found</body></html>".getBytes());
			exchange.getResponseBody().close();
			return;
		}

		
		//System.out.println("New listener: " + exchange.getRemoteAddress().getAddress().getHostAddress());
		
		
		//Headers headers = exchange.getResponseHeaders();
		
		
		
		
		if (pathTokens.hasMoreTokens())
		{
                    
                if (cast.isClosed()) {
                lastImage(exchange, cast);
                return;
                }
		
			String token = pathTokens.nextToken();
			Streamtype finalType = null;
			try {
				 finalType = Streamtype.valueOf(token);
				 if (finalType != Streamtype.forcedstream && finalType != Streamtype.forcedimage && finalType != Streamtype.forcedheadless){
				finalType = tryStreamtype(exchange.getRequestHeaders(),finalType);
				 }
			}catch(IllegalArgumentException ex)
			{
			//Nothing, finalType is null now
			}
			
			if (finalType == Streamtype.image || finalType == Streamtype.forcedimage)
			{
				image(exchange,cast);
				return;
			}
			else if (finalType == Streamtype.stream || finalType == Streamtype.forcedstream)
			{
				stream(exchange,cast);
				return;
			}
			else if (finalType == Streamtype.headless || finalType == Streamtype.forcedheadless)
			{
				headlessStream(exchange, cast);
				return;
			}
			
			/*if (token.equals("image") || (token.equals("stream") && exchange.getRequestHeaders().get("User-agent") == null)) { //Also return an image if no User-agent given
			
			image(exchange,cast);
			return;
		}*/
		/*else if (token.equals("stream")) {
				stream(exchange,cast);
				return;
		}*/
		
		}


		exchange.getResponseHeaders().set("Content-Type", "text/html");
		exchange.sendResponseHeaders(200,0);
		OutputStream out = exchange.getResponseBody();
		out.write(("<html><head><title>Stream " + streamID + "</title></head><body>").getBytes());
		printInfo(cast, streamID,out);
		out.write("</body>".getBytes());
		
		out.close();
		
		
		
	}
	
	private void printInfo(ImageSink cast, String streamID, OutputStream out) throws IOException
	{
		out.write((streamID + "<br>").getBytes());
                if (!cast.isClosed()) {
		out.write(("<a href='" + virtDir + "/" + streamID + "/" + Streamtype.forcedstream + "'>Stream</a> ").getBytes());
		out.write(("<a href='" + virtDir + "/" + streamID + "/" + Streamtype.forcedheadless + "'>Headless Stream</a> ").getBytes());
		out.write(("<a href='" + virtDir + "/" + streamID + "/" + Streamtype.stream + "'>Linkable Stream</a><br>").getBytes());
                } else {
                out.write("Stream closed<br>".getBytes());
                }
		out.write(("<img src='" + virtDir + "/" + streamID + "/" + Streamtype.forcedimage + "'></img>").getBytes());
		if (!cast.isClosed()) {
                out.write(("<br>Viewers: " + cast.streamListenerCount()).getBytes());
                }
	}
	private void stream(HttpExchange exchange, ImageSink cast) throws IOException
	{
		System.out.println("Requesting stream: " + exchange.getRemoteAddress().getAddress().getHostAddress());
		setResponseHeaders(exchange.getResponseHeaders());
		exchange.sendResponseHeaders(200,0);
		
		
	/*	DynamicOutputStreamMulticaster dos = new DynamicOutputStreamMulticaster();
		dos.addStream(new FileOutputStream("/home/testi/Desktop/unmapped"));
		
		ImmediateOutputStream im =new ImmediateOutputStream(new FileOutputStream("/home/testi/Desktop/mapped"),true);
		dos.addStream(im);
		dos.addStream(exchange.getResponseBody());
		
*/
		OutputStream responseBody = exchange.getResponseBody();
		cast.addStream(responseBody);

	}
	private void image(HttpExchange exchange, ImageSink cast) throws IOException
	{
		System.out.println("Requesting image: " + exchange.getRemoteAddress().getAddress().getHostAddress());
		setSingleImageResponseHeaders(exchange.getResponseHeaders());
		exchange.sendResponseHeaders(200,0);
		OutputStream responseBody = exchange.getResponseBody();
		cast.addSingleImageStream(responseBody);
	}
	private void headlessStream(HttpExchange exchange, ImageSink cast) throws IOException
	{
		System.out.println("Requesting headless stream: " + exchange.getRemoteAddress().getAddress().getHostAddress());
		setHeadlessResponseHeaders(exchange.getResponseHeaders());
		exchange.sendResponseHeaders(200,0);
		OutputStream responseBody = exchange.getResponseBody();

		cast.addHeadlessStream(responseBody);
	}
        private void lastImage(HttpExchange exchange, ImageSink cast) throws IOException
        {
        System.out.println("Requesting last image: " + exchange.getRemoteAddress().getAddress().getHostAddress());
        setSingleImageResponseHeaders(exchange.getResponseHeaders());
        exchange.sendResponseHeaders(200, 0);
        OutputStream responseBody = exchange.getResponseBody();
        cast.writeLastImage(responseBody);
        }
	
	private void listStreams(HttpExchange exchange) throws IOException
	{
		Headers headers = exchange.getResponseHeaders();
		headers.set("Content-Type", "text/html");
		exchange.sendResponseHeaders(200,0);
		OutputStream out = exchange.getResponseBody();
		out.write("<html><head><title>Available Streams</title></head><body>".getBytes());
		synchronized(casts) {
		if (casts.isEmpty())
		{
			out.write("No streams available".getBytes());
		} else {
			for (String t : casts.keySet()){
				printInfo(casts.get(t),t, out);
				out.write("<br><br>".getBytes());
				//out.write(("<a href='" + virtDir + "/" + t +"/stream'>Stream " + t + "</a><br><img src='" + virtDir + "/" + t + "/image'></img><br>").getBytes());
			}
			
		}
		
		}
		out.write("</body></html>".getBytes());
		out.close();	

	}
	
	public String addCast(String identifier, ImageSink stream)
	{
		synchronized(casts) {
		String newIdentifier=identifier;
		int i = 1;
		while (casts.containsKey(newIdentifier) && !casts.get(newIdentifier).isClosed()){
			newIdentifier=identifier + ":" + i;
			i++;
		}
		casts.put(newIdentifier, stream);
		return newIdentifier;
		}
	}
	public void addReplacingCast(String identifier, ImageSink stream)
	{
		synchronized(casts) {
		casts.put(identifier, stream);
		}
	}
	public void removeCast(String identifier)
	{
		synchronized(casts) {
		casts.remove(identifier);
		}
	}
	abstract protected void setResponseHeaders(Headers headers);
	abstract protected void setSingleImageResponseHeaders(Headers headers);
	abstract protected void setHeadlessResponseHeaders(Headers headers);
	
	/**
	 * @param headers of the request client
	 * @param the requested stream type
	 * @return the same type or a fallback type, or null for no type
	 */
	abstract protected Streamtype tryStreamtype(Headers headers, Streamtype type);
	//abstract protected void writeIntro(OutputStream responseStream) throws IOException;

}
