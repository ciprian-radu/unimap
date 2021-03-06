package ro.ulbsibiu.acaps.viewer.layout;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.security.acl.Owner;
import java.util.Hashtable;
import java.util.Map;

import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.ProgressMonitor;
import javax.swing.SwingUtilities;
import javax.swing.filechooser.FileFilter;

import org.jgraph.JGraph;
import org.jgraph.graph.DefaultGraphModel;
import org.jgraph.graph.GraphConstants;
import org.jgraph.graph.GraphLayoutCache;

import ro.ulbsibiu.acaps.viewer.svg.SvgGraphWriter;

import com.jgraph.layout.JGraphFacade;
import com.jgraph.layout.JGraphLayout;
import com.jgraph.layout.hierarchical.JGraphHierarchicalLayout;
import com.jgraph.layout.organic.JGraphFastOrganicLayout;
import com.jgraph.layout.organic.JGraphOrganicLayout;
import com.jgraph.layout.organic.JGraphSelfOrganizingOrganicLayout;
import com.jgraph.layout.tree.JGraphCompactTreeLayout;
import com.jgraph.layout.tree.JGraphRadialTreeLayout;
import com.jgraph.layout.tree.JGraphTreeLayout;
import com.l2fprod.common.swing.JTaskPane;
import com.l2fprod.common.swing.JTaskPaneGroup;

public class JGraphLayoutPanel extends JPanel {

	/** autogenerated serial version UID */
	private static final long serialVersionUID = 8095670508480099192L;

	protected JGraph graph = new JGraph(new DefaultGraphModel());

	protected JTaskPane taskPane = new JTaskPane();

	protected JCheckBox flushOriginCheckBox = new JCheckBox("Flush", true),
			directedCheckBox = new JCheckBox("Directed", true);
	
	protected JButton exportButton = new JButton();

	/**
	 * Holds the morphing manager.
	 */
	protected JGraphLayoutMorphingManager morpher = new JGraphLayoutMorphingManager();

	public JGraphLayoutPanel(JGraph graph) {
		this (graph, null);
	}
	
	@SuppressWarnings("deprecation")
	public JGraphLayoutPanel(JGraph graph, final String graphName) {
		super(new BorderLayout());
		setBorder(BorderFactory.createLineBorder(Color.DARK_GRAY));
		
		this.graph = graph;

		// Configures the graph
		graph.setGridSize(4);
		graph.setGridEnabled(true);
		graph.setAntiAliased(true);
		graph.setCloneable(true);

		exportButton.setAction(new AbstractAction("Export") {

			@Override
			public void actionPerformed(ActionEvent e) {
				JFileChooser jfc = new JFileChooser(new File("."));
				jfc.setFileFilter(new FileFilter() {

					@Override
					public String getDescription() {
						return "Scalable Vector Graphics";
					}

					@Override
					public boolean accept(File f) {
						return f.isDirectory() || f.getName().endsWith(".svg");
					}
				});
				if (graphName != null && !graphName.isEmpty()) {
					jfc.setSelectedFile(new File(graphName + ".svg"));
				}
				jfc.showSaveDialog(JGraphLayoutPanel.this);
				File selectedFile = jfc.getSelectedFile();
				int overwrite = JOptionPane.YES_OPTION;
				if (selectedFile.exists()) {
					overwrite = JOptionPane.showConfirmDialog(
							JGraphLayoutPanel.this, "File " + selectedFile
									+ " exists. Overwrite?");
				}
				if (overwrite == JOptionPane.YES_OPTION) {
					try {
						JGraphLayoutPanel.this.writeSVG(new FileOutputStream(
								selectedFile));
					} catch (FileNotFoundException exc) {
						JOptionPane jop = new JOptionPane(exc
								.getLocalizedMessage(),
								JOptionPane.ERROR_MESSAGE);
						jop.setVisible(true);
						exc.printStackTrace();
					}
				}
			}
		});
		
		// Configures the taskpane
		JTaskPaneGroup taskGroup = new JTaskPaneGroup();
		taskGroup.setText("Layout");
		taskGroup.add(new AbstractAction("Hierarchical") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 4371591757242568030L;

			public void actionPerformed(ActionEvent e) {
				execute(new JGraphHierarchicalLayout());
			}
		});
		taskGroup.add(new AbstractAction("Fast Organic") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 2951155480281239408L;

			public void actionPerformed(ActionEvent e) {
				JGraphFastOrganicLayout layout = new JGraphFastOrganicLayout();
				layout.setForceConstant(60);
				execute(layout);
			}
		});
		taskGroup.add(new AbstractAction("Organic") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = -8358332580527396301L;

			public void actionPerformed(ActionEvent e) {
				JGraphOrganicLayout layout = new JGraphOrganicLayout();
				layout.setOptimizeBorderLine(false);
				execute(layout);
			}
		});

		taskGroup.add(new AbstractAction("Self-Organizing") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 5304940004037952441L;

			public void actionPerformed(ActionEvent e) {
				JGraphSelfOrganizingOrganicLayout layout = new JGraphSelfOrganizingOrganicLayout();
				layout.setStartRadius(4);
				layout.setMaxIterationsMultiple(40);
				layout.setDensityFactor(20000);
				execute(new JGraphSelfOrganizingOrganicLayout());
			}
		});
		taskGroup.add(new AbstractAction("Compact Tree") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = -1738730569383603358L;

			public void actionPerformed(ActionEvent e) {
				execute(new JGraphCompactTreeLayout());
			}
		});
		taskGroup.add(new AbstractAction("Radialtree") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 3867686168321873240L;

			public void actionPerformed(ActionEvent e) {
				execute(new JGraphRadialTreeLayout());
			}
		});
		taskGroup.add(new AbstractAction("Tree") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 8917041471742851932L;

			public void actionPerformed(ActionEvent e) {
				execute(new JGraphTreeLayout());
			}
		});
		taskGroup.add(new AbstractAction("Reset") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = -2356309488712640292L;

			public void actionPerformed(ActionEvent e) {
				reset();
			}
		});
		// taskGroup.add(new AbstractAction("Tilt") {
		// public void actionPerformed(ActionEvent e) {
		// execute(new JGraphSimpleLayout(JGraphSimpleLayout.TYPE_TILT,
		// 100, 100));
		// }
		// });
		// taskGroup.add(new AbstractAction("Random") {
		// public void actionPerformed(ActionEvent e) {
		// execute(new JGraphSimpleLayout(JGraphSimpleLayout.TYPE_RANDOM,
		// 640, 480));
		// }
		// });

		taskPane.add(taskGroup);

		taskGroup = new JTaskPaneGroup();
		taskGroup.setText("Graph");
		taskGroup.add(new AbstractAction("Actual Size") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 383051696699856304L;

			public void actionPerformed(ActionEvent e) {
				JGraphLayoutPanel.this.graph.setScale(1);
			}
		});
		taskGroup.add(new AbstractAction("Fit Window") {
			/** autogenerated serial version UID */
			private static final long serialVersionUID = 2358014677157113239L;

			public void actionPerformed(ActionEvent e) {
				JGraphLayoutMorphingManager.fitViewport(JGraphLayoutPanel.this.graph);
			}
		});
		taskPane.add(taskGroup);

		taskGroup = new JTaskPaneGroup();
		taskGroup.setText("Options");
		taskGroup.add(exportButton);
		flushOriginCheckBox.setOpaque(false);
		taskGroup.add(flushOriginCheckBox);
		directedCheckBox.setOpaque(false);
		taskGroup.add(directedCheckBox);
		taskPane.add(taskGroup);

		// Adds the split pane
		JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
				new JScrollPane(taskPane), new JScrollPane(graph));
		add(splitPane, BorderLayout.CENTER);

		// Adds the status bar
		JLabel version = new JLabel(JGraph.VERSION);
		version.setBorder(BorderFactory.createEmptyBorder(2, 2, 2, 2));
		version.setFont(version.getFont().deriveFont(Font.PLAIN));
		add(version, BorderLayout.SOUTH);
		
		reset();
	}

	public void writeSVG(OutputStream out) {
		SvgGraphWriter svgGraphWriter = new SvgGraphWriter();
		GraphLayoutCache graphLayoutCache = graph.getGraphLayoutCache();
		svgGraphWriter.write(out, null, graphLayoutCache, 0);
	}
	
	/**
	 * Resets the graph to a circular layout.
	 */
	public void reset() {
		execute(new JGraphHierarchicalLayout());
		graph.clearSelection();
		JGraphLayoutMorphingManager.fitViewport(graph);
	}

	/**
	 * Executes the current layout on the current graph by creating a facade and
	 * progress monitor for the layout and invoking it's run method in a
	 * separate thread so this method call returns immediately. To display the
	 * result of the layout algorithm a {@link JGraphLayoutMorphingManager} is
	 * used.
	 */
	public void execute(final JGraphLayout layout) {
		if (graph != null && graph.isEnabled() && graph.isMoveable()
				&& layout != null) {
			final JGraphFacade facade = createFacade(graph);

			final ProgressMonitor progressMonitor = (layout instanceof JGraphLayout.Stoppable) ? createProgressMonitor(
					graph, (JGraphLayout.Stoppable) layout)
					: null;
			new Thread() {
				public void run() {
					synchronized (this) {
						try {
							// Executes the layout and checks if the user has
							// clicked
							// on cancel during the layout run. If no progress
							// monitor
							// has been displayed or cancel has not been pressed
							// then
							// the result of the layout algorithm is processed.
							layout.run(facade);

							SwingUtilities.invokeLater(new Runnable() {
								@SuppressWarnings("rawtypes")
								public void run() {
									boolean ignoreResult = false;
									if (progressMonitor != null) {
										ignoreResult = progressMonitor
												.isCanceled();
										progressMonitor.close();
									}
									if (!ignoreResult) {

										// Processes the result of the layout
										// algorithm
										// by creating a nested map based on the
										// global
										// settings and passing the map to a
										// morpher
										// for the graph that should be changed.
										// The morpher will animate the change
										// and then
										// invoke the edit method on the graph
										// layout
										// cache.
										Map map = facade.createNestedMap(true,
												(flushOriginCheckBox
														.isSelected()) ? true
														: false);
										morpher.morph(graph, map);
										graph.requestFocus();
									}
								}
							});
						} catch (Exception e) {
							e.printStackTrace();
							JOptionPane
									.showMessageDialog(graph, e.getMessage());
						}
					}
				}
			}.start(); // fork
		}
	}

	/**
	 * Creates a {@link JGraphFacade} and makes sure it contains a valid set of
	 * root cells if the specified layout is a tree layout. A root cell in this
	 * context is one that has no incoming edges.
	 * 
	 * @param graph
	 *            The graph to use for the facade.
	 * @return Returns a new facade for the specified layout and graph.
	 */
	protected JGraphFacade createFacade(JGraph graph) {
		// Creates and configures the facade using the global switches
		JGraphFacade facade = new JGraphFacade(graph, graph.getSelectionCells());
		facade.setIgnoresUnconnectedCells(true);
		facade.setIgnoresCellsInGroups(true);
		facade.setIgnoresHiddenCells(true);
		facade.setDirected(directedCheckBox.isSelected());

		// Removes all existing control points from edges
		facade.resetControlPoints();
		return facade;
	}

	/**
	 * Creates a {@link JGraphLayoutProgressMonitor} for the specified layout.
	 * 
	 * @param graph
	 *            The graph to use as the parent component.
	 * @param layout
	 *            The layout to create the progress monitor for.
	 * @return Returns a new progress monitor.
	 */
	protected ProgressMonitor createProgressMonitor(JGraph graph,
			JGraphLayout.Stoppable layout) {
		ProgressMonitor monitor = new JGraphLayoutProgressMonitor(graph,
				((JGraphLayout.Stoppable) layout).getProgress(),
				"PerformingLayout");
		monitor.setMillisToDecideToPopup(100);
		monitor.setMillisToPopup(500);
		return monitor;
	}

	/**
	 * Hook from GraphEd to set attributes of a new cell
	 */
	@SuppressWarnings("rawtypes")
	public Map createCellAttributes(Point2D point) {
		Map map = new Hashtable();
		// Snap the Point to the Grid
		point = graph.snap((Point2D) point.clone());
		// Add a Bounds Attribute to the Map
		GraphConstants.setBounds(map, new Rectangle2D.Double(point.getX(),
				point.getY(), 0, 0));
		// Make sure the cell is resized on insert
		GraphConstants.setResize(map, true);
		// Add a nice looking gradient background
		GraphConstants.setGradientColor(map, Color.blue);
		// Add a Border Color Attribute to the Map
		GraphConstants.setBorderColor(map, Color.black);
		// Add a White Background
		GraphConstants.setBackground(map, Color.white);
		// Make Vertex Opaque
		GraphConstants.setOpaque(map, true);
		GraphConstants.setInset(map, 2);
		GraphConstants.setGradientColor(map, new Color(200, 200, 255));
		return map;
	}

	/**
	 * Hook from GraphEd to set attributes of a new edge
	 */
	@SuppressWarnings("rawtypes")
	public Map createEdgeAttributes() {
		Map map = new Hashtable();
		// Add a Line End Attribute
		GraphConstants.setLineEnd(map, GraphConstants.ARROW_SIMPLE);
		// Add a label along edge attribute
		GraphConstants.setLabelAlongEdge(map, true);
		// Adds a parallel edge router
		GraphConstants.setLineStyle(map, GraphConstants.STYLE_SPLINE);
		GraphConstants.setFont(map, GraphConstants.DEFAULTFONT.deriveFont(10f));
		return map;
	}

}
