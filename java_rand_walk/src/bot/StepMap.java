package bot;
import java.util.Arrays;
import java.util.Collections;

public class StepMap {

	private Map m;
	private int[][] content;

	public StepMap(Map map) {
		m = map;
		content = new int[m.getWidth()][m.getHeight()];
		for(int i = 0; i < m.getWidth(); i++){
			for(int j = 0; j < m.getHeight(); j++){
				content[i][j] = 0;
			}
		}
	}
	public void upMap(Map map) {
		m = map;
	}
	public Direction checkOpen(){
		for(Direction d : Direction.values()){
			if(m.isAllowedOpen(d)){
				return d;
			}
		}
		return null;
	}
	public Direction randomWalk(){
		Position p = m.getPlayerPosition() ;
		Position p2;
		int minval = -1;
		int val;
		Direction[] myDirs = Direction.values();
		for (Direction d : myDirs){
			if (m.isAllowedMove(d)){
				p2 = Position.add(p,d);
				val = content[p2.getLine()][p2.getColumn()];
				if (minval == -1 || minval > val)
					minval = val;
			}
		}
		Collections.shuffle(Arrays.asList(myDirs));
		for (Direction d : myDirs){
			p2 = Position.add(p,d);
			val = content[p2.getLine()][p2.getColumn()];
			if (m.isAllowedMove(d) && val == minval ){
				content[p2.getLine()][p2.getColumn()]++;
				return d;
			}
		}
		return null;
	}
	public String toString(){
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i < m.getWidth(); i++){
			for(int j = 0; j < m.getHeight(); j++){
				sb.append(content[i][j]);
				sb.append(" ");
			}
			sb.append("\n");
		}
		return sb.toString();
	}
}
