package yunikorn.yukon.http;


import java.io.IOException;
import java.io.OutputStream;
//import yunikorn.core.*;
import java.io.*;
import java.util.*;
import java.net.*;
import yunikorn.sink.*;
import yunikorn.yukon.*;
import com.sun.net.httpserver.*;
import yunikorn.core.chunkstream.*;
//import yunikorn.sink.*;


public class YukonHttpRepeater implements HttpHandler {

	

	//DynamicOutputStreamMultiplexer dynamicMultiplexer;
	Map<String, YukonStreamRepeater> casts;

	String virtDir;
	public YukonHttpRepeater(String virtDir) {
		super();
		this.virtDir = virtDir;
		//this.dynamicMultiplexer = dynamicMultiplexer;
		casts = new HashMap<String, YukonStreamRepeater>(); 
	}

	public void handle(HttpExchange exchange) throws IOException {
		
		InputStream requestBody = exchange.getRequestBody();
		
		
		while(requestBody.read()!=-1)
		{
		}
		

		
		URI uri = exchange.getRequestURI();
		StringTokenizer pathTokens = new StringTokenizer(uri.getPath(),"/");
		if (!pathTokens.hasMoreTokens()) {
			exchange.sendResponseHeaders(404,0);
			Headers headers = exchange.getResponseHeaders();
			headers.set("Content-Type", "text/html");
			exchange.getResponseBody().write("Not found".getBytes());
			exchange.getResponseBody().close();
			return;
		}
		pathTokens.nextToken();
		if (!pathTokens.hasMoreTokens())
		{
			listStreams(exchange);
			return;
		}
		//try {
			
		String streamID = pathTokens.nextToken();
		YukonStreamRepeater cast=null;
		synchronized (casts) {
		cast = casts.get(streamID);
		if (cast == null)
		{
			Headers headers = exchange.getResponseHeaders();
			headers.set("Content-Type", "text/html");
			exchange.sendResponseHeaders(404,0);
			exchange.getResponseBody().write("<html><head><title>Error</title></head><body>Stream not found</body></html>".getBytes());
			exchange.getResponseBody().close();
			return;
		}
		}
		//System.out.println("New listener: " + exchange.getRemoteAddress().getAddress().getHostAddress());
		
		
		//Headers headers = exchange.getResponseHeaders();
		
		
		
		

				stream(exchange,cast);	
	}
	
	private void printInfo(YukonStreamRepeater cast, String streamID, OutputStream out) throws IOException
	{
		out.write((streamID + "<br>").getBytes());
		out.write(("<a href='" + virtDir + "/" + streamID + "'>Stream</a>").getBytes());
		//out.write(("Viewers: " + cast.streamListenerCount()).getBytes());
	}
	private void stream(HttpExchange exchange, YukonStreamRepeater cast) throws IOException
	{
		System.out.println("Requesting stream: " + exchange.getRemoteAddress().getAddress().getHostAddress());
		exchange.getResponseHeaders().set("Content-Type","application/octet-stream");
		exchange.sendResponseHeaders(200,0);
		OutputStream responseBody = exchange.getResponseBody();
		Streamer streamer = new Streamer(new ThreadedOutputStream(responseBody, true), cast);
		cast.addStreamEventListener(streamer);
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
	
	public String addCast(String identifier, YukonStreamRepeater stream)
	{
		synchronized(casts) {
		String newIdentifier=identifier;
		int i = 1;
		while (casts.containsKey(newIdentifier)){
			newIdentifier=identifier + ":" + i;
			i++;
		}
		casts.put(newIdentifier, stream);
		return newIdentifier;
		}
	}
	public void addReplacingCast(String identifier, YukonStreamRepeater stream)
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

	
	private class Streamer implements StreamEventListener
	{

		OutputStream out;
		StreamEventObservable parent;

		
		public Streamer(OutputStream out, StreamEventObservable parent) {
			super();
			this.out = out;
			this.parent = parent;
		}

		public void onStreamEvent(StreamEvent event) {
			try {
			event.write(out);
			out.flush();
			} catch (IOException ex)
			{
				parent.removeStreamEventListener(this);
				System.err.println(ex);
			}
			
		}

		public void onEndOfStream() {
			// TODO Auto-generated method stub
			try {
			out.close();
			}
			 catch (IOException ex)
				{
				 parent.removeStreamEventListener(this);	
				 System.err.println(ex);
				}
			
			}
		
	}
}
