package ro.ulbsibiu.acaps.e3s.ctg;

import org.jgrapht.graph.DefaultWeightedEdge;

/**
 * @author Ciprian Radu
 *
 */
public class E3sEdge extends DefaultWeightedEdge {

	/** autogenerated serial version UID */
	private static final long serialVersionUID = 2921906833046975991L;

	private String name;
	
	/** the name of the source vertex */
	private String from;
	
	/** the name of the target vertex */
	private String to;
	
	private String type;
	
	private double weight;
	
	public E3sEdge(String name, String from, String to, String type) {
		this.name = name;
		this.from = from;
		this.to = to;
		this.type = type;
	}

	public String getName() {
		return name;
	}
	
	public String getFrom() {
		return from;
	}
	
	public String getTo() {
		return to;
	}

	public String getType() {
		return type;
	}

	public double getWeight() {
		return weight;
	}

	public void setWeight(double weight) {
		this.weight = weight;
	}

	@Override
	public String toString() {
		// return "ARC " + name + " FROM " + from + " TO " + to + " TYPE " + type;
		
		// this is used for the label of the edge
		return Double.toString(weight);
	}
	
}
