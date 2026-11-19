import matplotlib.pyplot as plt

points = [[71, -89], [-75, -89], [-9, 11], [-24, -89], [-51, -89], [-77, -89], [42, 11]]
x, y = zip(*points)

fig, ax = plt.subplots()
scatter = ax.scatter(x, y)

# Annotate on hover
annot = ax.annotate(
    "",
    xy=(0, 0),
    xytext=(10, 10),
    textcoords="offset points",
    bbox=dict(boxstyle="round", fc="w"),
    arrowprops=dict(arrowstyle="->"),
)
annot.set_visible(False)


def update_annot(ind):
    idx = ind["ind"][0]
    pos = scatter.get_offsets()[idx]
    annot.xy = pos
    annot.set_text(f"({int(pos[0])}, {int(pos[1])})")
    annot.get_bbox_patch().set_facecolor("yellow")
    annot.get_bbox_patch().set_alpha(0.8)


def hover(event):
    vis = annot.get_visible()
    if event.inaxes == ax:
        cont, ind = scatter.contains(event)
        if cont:
            update_annot(ind)
            annot.set_visible(True)
            fig.canvas.draw_idle()
        else:
            if vis:
                annot.set_visible(False)
                fig.canvas.draw_idle()


fig.canvas.mpl_connect("motion_notify_event", hover)

plt.grid(True)
plt.xlabel("X")
plt.ylabel("Y")
plt.title("2D Points Visualization")
plt.show()
