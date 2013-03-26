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
    String dir;
    
	
    public Bot(){
	dungeonLevel = 0;
	map = null;
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
	case MAP: map = (Map)i.getValue(); break;
	}
    }

    public void start(){
	try{
	    while(true){
		Logger.println("READING FROM SOCKET");
		nextTurn();
		Logger.println("DOING TURN");
		doTurn();
	    }

	}catch(IOException e){
	    e.printStackTrace();
	    return;
	}catch(UnknownPositionException e){
	    System.out.println("The player location has not been found, game has ended");
	}
    }
	
    public void doTurn(){
	Position myPosition = new Position(0,0);
	Square[] squareTab = new Square[10];
	String action;
	
	myPosition = getPlayerPosition();
	SquareTab.getSquareAround(myPosition);
	if (dir.equals("NORTH")){
	    
	    if (squareTab[2].type=HORIZONTAL_WALL){
		double dice = Math.random();
		if (dice > 0.7){
		    myDir = new Direction("WEST",-1,0);
		    dir = "WEST";
		    myParser.broadcastMove(myDir);
		    nextTurn();
		}
		else{
		    myParser.broadcastSearch();
		    nextTurn();
		}
		
	    }
	    if (squareTab[6].type=VERTICAL_WALL){
		double dice = Math.random();
		if (dice < 0.7){
		    myParser.broadcastSearch();
		    nextTurn();
		}
		else
		    {
			myDir = new Direction("WEST",-1,0);
			dir = "WEST";
			myParser.broadcastMove(myDir);
			nextTurn();
		    }
		
	    }
	    
	    if (squareTab[4].type=VERTICAL_WALL){
		double dice = Math.random();
		if (dice < 0.7){
		    myParser.broadcastSearch();
		    nextTurn();
		}
		else
		    {
			myDir = new Direction("WEST",-1,0);
			dir = "WEST";
			myParser.broadcastMove(myDir);
			nextTurn();
		    }
	}
       	
	if (dir.equals("WEST")){
	    if (squareTab[2].type=VERTICAL_WALL){
		double dice = Math.random();
		if (dice > 0.7){
		    myDir = new Direction("SOUTH",0,-1);
		    dir = "SOUTH";
		    myParser.broadcastMove(myDir);
		    nextTurn();
		}
		else{
		    myParser.broadcastSearch();
		    nextTurn();
		}	
	    }
	    if (squareTab[2].type=HORIZONTAL_WALL){
		double dice = Math.random();
		if (dice < 0.7){
		    myParser.broadcastSearch();
		    nextTurn();
		}
		else
		    {
			myDir = new Direction("WEST",-1,0);
			dir = "WEST";
			myParser.broadcastMove(myDir);
			nextTurn();
		    }
		
	    }
	    
	    if (squareTab[8].type=HORIZONTAL_WALL){
		double dice = Math.random();
		if (dice < 0.7){
		    myParser.broadcastSearch();
		    nextTurn();
		}
		else
		    {
			myDir = new Direction("WEST",-1,0);
			dir = "WEST";
			myParser.broadcastMove(myDir);
			nextTurn();
		    }
		
	    }

	    if (dir.equals("SOUTH")){
		if (squareTab[8].type=HORIZONTAL_WALL){
		    double dice = Math.random();
		    if (dice > 0.7){
			myDir = new Direction("EAST",1,0);
			dir = "EAST";
			myParser.broadcastMove(myDir);
			nextTurn();
		    }
		    else{
			myParser.broadcastSearch();
			nextTurn();
		    }	
		}
		if (squareTab[4].type=VERTICAL_WALL){
		    double dice = Math.random();
		    if (dice < 0.7){
			myParser.broadcastSearch();
			nextTurn();
		    }
		    else
			{
			    myDir = new Direction("SOUTH",-1,0);
			    dir = "SOUTH";
			    myParser.broadcastMove(myDir);
			    nextTurn();
			}
		    
		}
		
		if (squareTab[6].type=HORIZONTAL_WALL){
		    double dice = Math.random();
		    if (dice < 0.7){
		    myParser.broadcastSearch();
		    nextTurn();
		    }
		    else
			{
			    myDir = new Direction("SOUTH",-1,0);
			    dir = "SOUTH";
			    myParser.broadcastMove(myDir);
			    nextTurn();
			}
		
		}
	    }
	    if (dir.equals("EAST")) {
		if (squareTab[8].type=VERTICAL_WALL){
		    double dice = Math.random();
		    if (dice > 0.7){
			myDir = new Direction("NORTH",1,0);
			dir = "NORTH";
			myParser.broadcastMove(myDir);
			nextTurn();
		    }
		    else{
			myParser.broadcastSearch();
			nextTurn();
		    }	
		}
		if (squareTab[8].type=HORIZONTAL_WALL){
		    double dice = Math.random();
		    if (dice < 0.7){
			myParser.broadcastSearch();
			nextTurn();
		    }
		    else
			{
			    myDir = new Direction("EAST",0,1);
			    dir = "EAST";
			    myParser.broadcastMove(myDir);
			    nextTurn();
			}
		    
		}
		
		if (squareTab[2].type=HORIZONTAL_WALL){
		    double dice = Math.random();
		    if (dice < 0.7){
			myParser.broadcastSearch();
			nextTurn();
		    }
		    else
			{
			    myDir = new Direction("EAST",-1,0);
			    dir = "EAST";
			    myParser.broadcastMove(myDir);
			    nextTurn();
			}
		}
		
	    }
	}
	}
	
    }
    
	
    public Square[] getSquareAround(Position p)
    {
	Position position_no = new Position(p.line+1,p.column-1);
	Position position_n = new Position(p.line+1,p.column);
	Position position_ne = new Position(p.line+1,p.column+1);
	Position position_e = new Position(p.line,p.column+1);
	Position position_se = new Position(p.line-1,p.column+1);
	Position position_s = new Position(p.line-1,p.column);
	Position position_so = new Position(p.line-1,p.column-1);
	Position position_o = new Position(p.line,p.column-1);
	Square [] squareTab = new Square[10];
	squareTab[1] = getSquare(position_no);
	squareTab[2] = getSquare(position_n);
	squareTab[3] = getSquare(position_ne);
	squareTab[4] = getSquare(position_o);
	squareTab[6] = getSquare(position_e);
	squareTab[7] = getSquare(position_so);
	squareTab[8] = getSquare(position_s);
	squareTab[9] = getSquare(position_no);
	return SquareTab;
    }
	
	
    public void randomAction(){
	double dice = Math.random();
	if (dice > 0.7)
	    myParser.broadcastSearch();
	else
	    randomMoveOrOpen();
			
    }
	
    public void randomMove(){
	Direction[] myDirs = Direction.values();
	Collections.shuffle(Arrays.asList(myDirs));
	for (Direction d : myDirs){
	    if (map.isAllowedMove(d)){
		myParser.broadcastMove(d);
		return;
	    }
	}
    }
	
    public void randomMoveOrOpen(){
	Direction[] myDirs = Direction.values();
	Collections.shuffle(Arrays.asList(myDirs));
	for (Direction d : myDirs){
	    if (map.isAllowedMove(d)){
		myParser.broadcastMove(d);
		return;
	    }
	    if (map.isAllowedOpen(d)){
		myParser.broadcastOpeningDoor(d);
		return;
	    }
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

