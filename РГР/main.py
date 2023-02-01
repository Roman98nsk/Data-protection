import random
import networkx as nx
import matplotlib.pyplot as plt
import graph_params as gp

# Функция добавления линии графа
def add_edge(f_item, s_item, graph = None, color = 'black'):
    graph.add_edge(f_item, s_item, color=color)
    graph.add_edge(s_item, f_item, color=color)

# Рисует граф
def graph_drawing(graph_info, show_cycle = False, cycle = None):
    graph = nx.Graph()
    if not show_cycle and not cycle:
        graph.add_nodes_from(graph_info.keys())
    else:
        for node in graph_info.keys():
            if node == cycle[0] or node == cycle[len(cycle)-1]:
                graph.add_node(node, color = 'blue')
            else:
                graph.add_node(node, color = 'gray')
    # Создает связи между точками
    for vertex in graph_info.keys():
        for edge in graph_info.get(vertex):
            add_edge(vertex, edge, graph)
    # Раскрашивает связи если передан гамильтонов цикл
    if show_cycle and cycle:
        for i in range(0, 20):
            if i < 19:
                add_edge(cycle[i], cycle[i + 1], graph, color = 'g')
            else:
                add_edge(cycle[0], cycle[i], graph, color = 'g')
    # Рисует раскрашеный граф, если есть цикл
    if show_cycle:
        colors_edge = nx.get_edge_attributes(graph, 'color').values()
        colors_nodes = nx.get_node_attributes(graph, 'color').values()
        nx.draw_spring(graph, edge_color = colors_edge, node_color = colors_nodes, node_size = 1000, with_labels = True)
    # Рисует не раскрашеный граф
    else:
        nx.draw_spring(graph, edge_color = 'red', node_color = 'yellow', node_size = 1000, with_labels = True)
    plt.show()

def shuffle(graph_info: dict, cycle: list):
    new_graph = {}
    new_cycle = []
    repl = [str(i) for i in graph_info.keys()]
    dictionary = {}
    # В ходе цикла меняет названия всех вершин графа
    for i in graph_info.keys():
        choise = random.choice(repl)
        repl.remove(choise)
        dictionary[i] = choise

    # Переименовывает Вершины на полученные
    for key in graph_info.keys():
        for value in graph_info.get(key):
            if new_graph.get(dictionary.get(key)):
                new_graph[dictionary.get(key)].append(dictionary.get(value))
            else:
                new_graph[dictionary.get(key)] = [dictionary.get(value)]
    # Обновляет цикл в соответствии со словарем
    for i in cycle:
        new_cycle.append(dictionary.get(i))
    return new_graph, new_cycle, dictionary

if __name__ == "__main__":
    ig, gm, shuf = shuffle(gp.graph_info, gp.origin_graph_cycle)
    graph_drawing(ig) 
    num = int(input("Ответить на вопрос:\n1 -  Гамильтонов цикл изоморфного графа \n2 -  Доказать, что граф изоморфный\n"))
    if num == 1:
        print(f'Гамильтонов цикл: {gm}')
    if num == 2:
        print(f'Перестановка: {shuf}')
        print(f'Вершины и их пути: {ig}')
