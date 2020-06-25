import groovy.transform.CompileStatic

import java.util.ArrayList;
import java.util.List;
import java.util.LinkedHashSet;
import java.util.Set;

import rba.tool.model.rtool.*;

@CompileStatic
public class RTEventProcessings implements rba.tool.model.rtool.statemachine.IEventProcessings {
	
	List<RTEventProcessing> eventProcessings;
	
	/**
	 * 操作権調停クラスの構築
	 * @param model
	 */
	public void configure() {
		eventProcessings = new ArrayList<>();
		createEventProcessings();
	}
	
	   /**
	    * 操作権を持つエリアを取得
	    * @return areas
	    */
	   public List<RTArea> getFocusAreas() {
	       Set<RTArea> areas = new LinkedHashSet<RTArea>();
	       for (int i = 0; i < eventProcessings.size(); i++) {
	           RTEventProcessing eventProcessing = eventProcessings.get(i);
	           RTArea area = eventProcessing.execute();
	           if(area != null) {
	               areas.add(area);
	           }
	       }
	       return new ArrayList<>(areas);
	   }

	private void createEventProcessings() {
	}

}
