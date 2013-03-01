package bot;

import java.io.IOException;
import java.net.UnknownHostException;
import java.util.Arrays;
import java.util.Collections;

import util.Logger;

public class Bot {
	
	InputOutputUnit myParser;
	int dungeonLevel;
	Map map;
	StepMap steps;
	
	public Bot(){
		dungeonLevel = 0;
		map = null;
		steps = null;
		myParser = new InputOutputUnit();
	}
	
	public Bot(String hostname)
			throws UnknownHostException, IOException{
		this(hostname, Protocole.DEFAULT_PORT);
	}

	public Bot(String hostname, int port)
			throws UnknownHostException, IOException{
		this();
		myParser = new InputOutputUnit(hostname, port);
	}

	public void treatInformation(Information i) {
		switch (i.getVariable()){
		case DUNGEON_LEVEL: dungeonLevel = (Integer)i.getValue(); break;
		case MAP: 
			map = (Map)i.getValue(); 
			if (steps == null)
				steps = new StepMap(map);
			else
				steps.upMap(map);
			break;
		}
	}

	public void start(){
		try{
			while(true){
				Logger.println("READING FROM SOCKET");
				nextTurn();
				Logger.println("DOING TURN");
				doTurn();
				Logger.println("STEP MAP");
				Logger.println(steps.toString());
			}

		}catch(IOException e){
			e.printStackTrace();
			return;
		}catch(UnknownPositionException e){
			System.out.println("The player location has not been found, game has ended");
		}
	}
	
	public void doTurn(){
		randomAction();		
	}
	
	public void randomAction(){
		double dice = Math.random();
		if (dice > 0.7)
			myParser.broadcastSearch();
		else{
			Direction d = steps.checkOpen();
			if (d != null) {
				myParser.broadcastOpeningDoor(d);
				return;
			}
			d = steps.randomWalk();
			myParser.broadcastMove(d);
		}
			
	}
	
	public void nextTurn() throws IOException, UnknownPositionException{
		myParser.parseNextTurn(this);
	}
	
	@Override
	public String toString(){
		StringBuffer sb = new StringBuffer();
		sb.append("dungeon_level : " + dungeonLevel + "\n");
		if (map != null)
			sb.append(map.toString() + "\n");
		return sb.toString();
	}
}
