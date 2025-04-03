import matplotlib.pyplot as plot


def getProvinceGraph(xdata, ydata, title, source, var):

    for i in range(len(xdata)):
        xdata[i] = xdata[i][0:3].upper()

    plot.title(title)
    plot.xlabel("Provinces")
    plot.ylim(ymin = -1, ymax = max(ydata) + 1)
    plot.ylabel(f"{var} Values")
    plot.scatter(xdata, ydata, label = f"{var} From {source}")
    plot.legend(loc="upper left")
    plot.grid()
    plot.savefig(f'{title}.png')


    return 0

def altShowProvinceGraph():

    xdata = ["BRI", "ALB", "SAS", "ONT", "OTT", "QUE", "NOV", "NEW"]
    ydata = [5, 4, 2, 1, -1, 1, 3, 5]

    plot.title("Map of Provinces")
    plot.xlabel("Provinces")
    plot.ylim(ymin = -5, ymax = 2 * max(ydata))
    plot.scatter(xdata, ydata)
    plot.grid()
    plot.savefig('Test.png')

if __name__ == "__main__":

    altShowProvinceGraph()
