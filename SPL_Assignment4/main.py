import sys

from repository import repo


class Hat:
    def __init__(self, id, topping, supplier, quantity):
        self.id = int(id)
        self.topping = topping
        self.supplier = int(supplier)
        self.quantity = int(quantity)


class Supplier:
    def __init__(self, id, name):
        self.id = int(id)
        self.name = name


class Order:
    def __init__(self, id, location, hat):
        self.id = int(id)
        self.location = location
        self.hat = int(hat)


def main(args=sys.argv[1:]):
    repo.create_tables()
    with open(args[0]) as f:
        lines = f.readlines()
        (numOfHats, numOfSuppliers) = lines[0].strip().split(",")
        for i in range(1, len(lines)):
            if (i <= int(numOfHats)):
                repo.hats.insert(Hat(*lines[i].strip().split(",")))
            else:
                repo.suppliers.insert(Supplier(*lines[i].strip().split(",")))

    summaryFile = open(args[2], "w")
    with open(args[1]) as g:
        lines = g.readlines()
        j = 1
        for i in range(0, len(lines)):
            x = lines[i].strip().split(",")
            hat = repo.hats.find(x[1])
            if (hat != None):
                repo.hats.updateQuantity(x[1])
                repo.orders.insert(Order(j, x[0], hat.id))
                j += 1
                summaryFile.write(hat.topping + "," + repo.suppliers.find(hat.supplier).name + "," + x[0])
                summaryFile.write("\n")
    summaryFile.close()


if __name__ == '__main__':
    main()
