import matplotlib.pyplot as plt
import networkx as nx
import matplotlib.patches as patch


def getNodeGraph(paths, source, title):

    # actually create the figure, and set its title
    fig = plt.figure(figsize=(8,8))
    ax = plt.subplot(111)
    ax.set_title(f'Provinces and Paths for Source {source}', fontsize=10)

    # add all of the nodes (provinces)
    G = nx.DiGraph()
    G.add_nodes_from(['BRI', 'ALB', 'SAS', 'ONT','OTT','QUE','NOV','NEW'])

    # adding the paths and giving them specific colors and labels based on their position in paths
    for path in paths:
        for i in range(len(path) - 1):            
            if path == paths[0]:
                G.add_edge(path[i], path[i+1], color = 'red', label = 'Hops')
            elif path == paths[1]:
                G.add_edge(path[i], path[i+1], color = 'yellow', label = 'Distance')
            elif path == paths[2]:
                G.add_edge(path[i], path[i+1], color = 'blue', label = 'Time')
            else:
                G.add_edge(path[i], path[i+1], color = 'green', label = 'Dementors')

    # drawing the nodes and edges with appropriate colors
    edges = G.edges()
    colors = [G[u][v]['color'] for u,v in edges]
    pos = nx.shell_layout(G)
    nx.draw(G, pos, node_size=1500, node_color='yellow', edge_color = colors, font_size=8, font_weight='bold')
    nx.draw_networkx_labels(G, pos)

    # writing stuff for the legend, patch will render a patch of that color which can be used to manually create a legend
    r = patch.Patch(color='red', label='Hops')
    y = patch.Patch(color='yellow', label='Distance')
    b = patch.Patch(color='blue', label='Time')
    g = patch.Patch(color='green', label='Dementors')

    plt.tight_layout()
    plt.legend(handles = [r, y, b, g], loc = "upper left")
    
    # saving the figure
    plt.savefig(f"{title}.png")