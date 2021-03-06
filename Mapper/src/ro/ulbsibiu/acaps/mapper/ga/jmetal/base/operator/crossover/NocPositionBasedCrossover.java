package ro.ulbsibiu.acaps.mapper.ga.jmetal.base.operator.crossover;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;

import jmetal.base.Solution;
import jmetal.base.operator.crossover.Crossover;
import jmetal.base.variable.Permutation;
import jmetal.util.Configuration;
import jmetal.util.JMException;
import jmetal.util.PseudoRandom;

import org.apache.log4j.Logger;

import ro.ulbsibiu.acaps.mapper.sa.Core;

/**
 * This class allows to apply a Position based crossover operator on parent
 * solutions. It is a jMetal {@link Crossover} operator.
 * 
 * This crossover is aware of the Network-on-Chip application mapping problem.
 * It does not necessary fix the position of a parent randomly. Instead, it
 * analyzes the communications between the IP cores. It fixes the cores that
 * communicates the highest data volume (50% of the cores). Then, having this
 * cores fixed, it calculates the cost for each parent. The parent with the
 * minimum cost is selected for fixing the positions in the child (<b>this
 * crossover generates only one child</b>). So, the child will be generated by
 * the fixing the positions from the selected parent and rest of the genes will
 * be come from other parent.
 * 
 * NOTE: the type of those variables must be VariableType_.Permutation.
 * 
 * @author shaikat
 * @author cradu (code review)
 */
public abstract class NocPositionBasedCrossover extends Crossover {

	/**
	 * Communication class to hold source, destination and volume of the
	 * communication
	 * 
	 * @author shaikat
	 * @author cradu (code review)
	 */
	private static class Communication {
		
		private int sourceCore, destCore;
		
		private long volume;

		/**
		 * Constructor
		 * 
		 * @param sCore
		 *            id of source core
		 * @param dCore
		 *            id of destination core
		 * @param volume
		 *            volume of the communication
		 */
		public Communication(int sCore, int dCore, long volume) {
			sourceCore = sCore;
			destCore = dCore;
			this.volume = volume;
		}
		
	}

	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(NocPositionBasedCrossover.class);

	private ArrayList<Communication> communications;

	private int requiredNumberOfCommunications;

	private int requiredNumberOfCores;

	private int[] fixedCores;

	private Core[] cores;

	/** automatically generated serial version UID */
	private static final long serialVersionUID = 6065180546012402023L;

	private static Class<?> PERMUTATION_SOLUTION;

	/**
	 * Constructor
	 * 
	 * @param cores
	 *            the IP cores to be mapped
	 */
	public NocPositionBasedCrossover(Core[] cores) {
		try {
			PERMUTATION_SOLUTION = Class
					.forName("jmetal.base.solutionType.PermutationSolutionType");
		} catch (ClassNotFoundException e) {
			logger.error(
					"Couldn't find the PermutationSolutionType class (this crossover is for permutation problems only)",
					e);
		}
		this.cores = cores;
		doFindAndSortCommunications();
	}

	/**
	 * Finds the communications from cores array and save them in the
	 * communications class array. Then, it sorts the communications descending
	 * order according to volume of the communication (from high to low). Thus,
	 * it finds the cores from the communications (10->11, so cores are 10, 11)
	 * that will be fixed (50% of them) and save to fixedCores array (it also
	 * finds the required number of communications for fixing these cores).
	 */
	private void doFindAndSortCommunications() {
		communications = new ArrayList<Communication>();
		// find the communications from cores array and save it the
		// communications class array
		for (int i = 0; i < cores.length; i++) {
			for (int j = 0; j < cores[i].getToCommunication().length; j++) {
				if (cores[i].getToCommunication()[j] != 0) {
					communications.add(new Communication(i, j, cores[i]
							.getToCommunication()[j]));
				}

			}
		}
		// sort the communication array
		Collections.sort(communications, new Comparator<Communication>() {
			public int compare(Communication o1, Communication o2) {
				if (o1.volume < o2.volume)
					return 1;
				else if (o1.volume == o2.volume)
					return 0;
				else
					return -1;
			}
		});

		int[] fixedCores = new int[cores.length];
		int numberOfCommunications = 0;

		for (int i = 0; i < cores.length; i++) {
			fixedCores[i] = -1;
		}

		int indexFixedPosition = 0;

		// find fixed cores and required number of communications
		for (int i = 0; i < communications.size(); i++) {
			if (indexFixedPosition >= cores.length / 2 - 1) {
				break;
			}

			numberOfCommunications++;

			if (searchArray(fixedCores, communications.get(i).sourceCore) == -1) {
				fixedCores[indexFixedPosition++] = communications.get(i).sourceCore;
			}

			if (searchArray(fixedCores, communications.get(i).destCore) == -1) {
				fixedCores[indexFixedPosition++] = communications.get(i).destCore;
			}
		}

		if (logger.isDebugEnabled()) {
			logger.debug("Number of required cores " + indexFixedPosition);
			logger.debug("Fixed cores are " + Arrays.toString(fixedCores));
			logger.debug("Number of required Communications "
					+ numberOfCommunications);

		}

		requiredNumberOfCommunications = numberOfCommunications;
		requiredNumberOfCores = indexFixedPosition;
		this.fixedCores = fixedCores;
	}

	/**
	 * Searches for a value in a specified array
	 * 
	 * @param arr
	 *            the array
	 * @param key
	 *            the value
	 * @return if found, the array index (where the key is), -1 otherwise
	 */
	private int searchArray(int[] arr, int key) {
		int p = -1;

		for (int i = 0; i < arr.length; i++) {
			if (key == arr[i]) {
				p = i;
			}
		}

		return p;
	}

	/**
	 * Computes the number oh hops between two NoC nodes (requires NoC topology
	 * knowledge)
	 * 
	 * @param node1
	 *            the first NoC node
	 * @param node2
	 *            the second NoC node
	 * @return the distance between the two NoC nodes
	 */
	public abstract int computeDistance(int node1, int node2);
	
	/**
	 * calculate cost for the individual that send to the function
	 * 
	 * @param indv
	 *            individual array
	 * @return the cost of the individual using manhattan distance(only for the
	 *         required number of communications)
	 */
	private long calculateCost(int[] indv) {
		long cost = 0;
		for (int i = 0; i < requiredNumberOfCommunications; i++) {
			int positionOfSource = searchArray(indv, communications.get(i).sourceCore);
			if (positionOfSource == -1) {
				logger.fatal("Position of core "
						+ communications.get(i).sourceCore + " in individual "
						+ Arrays.toString(indv)
						+ " couldn't be determined! Exiting...");
				System.exit(0);
			}
			int positionOfDest = searchArray(indv, communications.get(i).destCore);
			if (positionOfDest == -1) {
				logger.fatal("Position of core "
						+ communications.get(i).destCore + " in individual "
						+ Arrays.toString(indv)
						+ " couldn't be determined! Exiting...");
				System.exit(0);
			}

			cost += computeDistance(positionOfSource, positionOfDest) * communications.get(i).volume;

		}

		if (logger.isDebugEnabled()) {
			logger.debug("Cost of the indv " + Arrays.toString(indv) + " is : " + cost);
		}
		
		return cost;
	}

	/**
	 * Find the positions of the fixed cores within the individual
	 * 
	 * @param indv
	 *            individual array
	 * @return the array of the position of the fixed cores
	 */
	private int[] findFixedPositions(int[] indv) {
		int[] fixedPositions = new int[requiredNumberOfCores];

		int i = 0;
		while (fixedCores[i] != -1) {
			fixedPositions[i] = searchArray(indv, fixedCores[i]);
			logger.assertLog(fixedPositions[i] != -1, "Fixed core "
					+ fixedCores[i] + " was not found in individual " + indv
					+ "!");
			i++;
		}
		if(logger.isDebugEnabled()){
			logger.debug("Fixed positions are "+ Arrays.toString(fixedPositions));
		}
		return fixedPositions;
	}

	/**
	 * Perform the crossover operation
	 * 
	 * @param probability
	 *            Crossover probability
	 * @param parent1
	 *            The first parent
	 * @param parent2
	 *            The second parent
	 * @return An array containig the two offsprings
	 * @throws JMException
	 */
	public Solution[] doCrossover(double probability, Solution parent1,
			Solution parent2) throws JMException {
		String fixedParent;
		int[] fixedPositions = new int[requiredNumberOfCores];

		Solution[] offspring = new Solution[1];

		offspring[0] = new Solution(parent1);

		if (PERMUTATION_SOLUTION.isAssignableFrom(parent1.getType().getClass())
				&& PERMUTATION_SOLUTION.isAssignableFrom(parent1.getType()
						.getClass())) {
			int permutationLength;

			permutationLength = ((Permutation) parent1.getDecisionVariables()[0])
					.getLength();

			int parent1Vector[] = ((Permutation) parent1.getDecisionVariables()[0]).vector_;
			int parent2Vector[] = ((Permutation) parent2.getDecisionVariables()[0]).vector_;
			int offspring1Vector[] = ((Permutation) offspring[0]
					.getDecisionVariables()[0]).vector_;

			if (PseudoRandom.randDouble() < probability) {
				// compare two parents to select which one is better and then
				// find the positions of the fixed cares
				if (calculateCost(parent1Vector) <= calculateCost(parent2Vector)) {
					fixedPositions = findFixedPositions(parent1Vector);
					fixedParent = "parent1";
				} else {
					fixedPositions = findFixedPositions(parent2Vector);
					fixedParent = "parent2";
				}

				// initialize the offsprings array
				for (int i = 0; i < offspring1Vector.length; i++) {
					offspring1Vector[i] = Integer.MIN_VALUE;
				}

				int[] tempParent = new int[permutationLength];

				if (fixedParent.equals("parent1")) {
					tempParent = Arrays.copyOf(parent2Vector,
							parent2Vector.length);
				} else {
					tempParent = Arrays.copyOf(parent1Vector,
							parent1Vector.length);
				}
				
				// copy the content of the specific position(setOfPosition) from
				// parent1 to child1. Also set Integer.MIN_VALUE in position of
				// parent2 (tempParent) where the content of the parent1 of the
				// specific position (setOfPosition) is matched
				for (int i = 0; i < fixedPositions.length; i++) {
					if (fixedParent.equals("parent1")) {
						offspring1Vector[fixedPositions[i]] = parent1Vector[fixedPositions[i]];
					} else {
						offspring1Vector[fixedPositions[i]] = parent2Vector[fixedPositions[i]];
					}
					for (int j = 0; j < tempParent.length; j++) {
						if (fixedParent.equals("parent1")) {
							if (tempParent[j] == parent1Vector[fixedPositions[i]]) {
								tempParent[j] = Integer.MIN_VALUE;
								break;
							}
						} else {
							if (tempParent[j] == parent2Vector[fixedPositions[i]]) {
								tempParent[j] = Integer.MIN_VALUE;
								break;
							}
						}
					}
				}
				
				 // starting from left to right of parent2(tempParent), copy
				 // content from parent2 to the rest of the position of child1 by
				 // skipping Integer.MIN_VALUE
				for (int i = 0; i < tempParent.length; i++) {
					if (tempParent[i] == Integer.MIN_VALUE) {
						continue;
					} else {
						for (int j = 0; j < offspring1Vector.length; j++) {
							if (offspring1Vector[j] != Integer.MIN_VALUE) {
								continue;
							} else {
								offspring1Vector[j] = tempParent[i];
								break;
							}
						}
					}
				}
				// child1 finished
				
				if(logger.isDebugEnabled()){
					logger.debug("Generated Offspring is " + Arrays.toString(offspring1Vector));
				}
				
			}// if
		} else {
			Configuration.logger_
					.severe("NocPositionBasedCrossover.doCrossover: invalid type");
			Class<?> cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".doCrossover()");
		}// else

		// doCrossover
		return offspring;
	}

	/**
	 * Executes the operation
	 * 
	 * @param object
	 *            An object containing an array of two solutions
	 * @throws JMException
	 */
	public Object execute(Object object) throws JMException {
		Solution[] parents = (Solution[]) object;
		Double crossoverProbability = null;

		if (!PERMUTATION_SOLUTION.isAssignableFrom(parents[0].getType()
				.getClass())
				|| !PERMUTATION_SOLUTION.isAssignableFrom(parents[1].getType()
						.getClass())) {

			Configuration.logger_
					.severe("NocPositionBasedCrossover.execute: the solutions "
							+ "are not of the right type. The type should be '"
							+ PERMUTATION_SOLUTION + "', but "
							+ parents[0].getType() + " and "
							+ parents[1].getType() + " are obtained");
		}

		// crossoverProbability = (Double)parameters_.get("probability");
		crossoverProbability = (Double) getParameter("probability");

		if (parents.length < 2) {
			Configuration.logger_
					.severe("NocPositionBasedCrossover.execute: operator needs two "
							+ "parents");
			Class<?> cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".execute()");
		} else if (crossoverProbability == null) {
			Configuration.logger_
					.severe("NocPositionBasedCrossover.execute: probability not "
							+ "specified");
			Class<?> cls = java.lang.String.class;
			String name = cls.getName();
			throw new JMException("Exception in " + name + ".execute()");
		}

		Solution[] offspring = doCrossover(crossoverProbability.doubleValue(),
				parents[0], parents[1]);

		return offspring;
	} // execute

}
