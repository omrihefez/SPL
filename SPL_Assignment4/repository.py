import sqlite3
import atexit
import sys


class Hat:
    def __init__(self, id, topping, supplier, quantity):
        self.id = id
        self.topping = topping
        self.supplier = supplier
        self.quantity = quantity


class Supplier:
    def __init__(self, id, name):
        self.id = id
        self.name = name


class Order:
    def __init__(self, id, location, hat):
        self.id = id
        self.location = location
        self.hat = hat


class Hats:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, hat):
        self._conn.execute(""" 
        INSERT INTO Hats (id,topping,supplier,quantity) VALUES (?,?,?,?)
        """, [hat.id, hat.topping, hat.supplier, hat.quantity])

    def find(self, hat_topping):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, topping, supplier , quantity From hats WHERE topping = ?
            """, [hat_topping])
        # if c.fetchone is None:
        #     return None
        hats = c.fetchall()
        hat = None
        min_id = sys.maxsize
        for line in hats:
            if line[2] < min_id:
                min_id = line[2]
                hat = Hat(*line)
        return hat

    def updateQuantity(self, hat_topping):
        hat = self.find(hat_topping)
        if hat is not None:
            if (hat.quantity > 1):
                self._conn.execute("""
                UPDATE hats SET quantity = ? WHERE id = ? """, [hat.quantity - 1, hat.id])
            else:
                self._conn.execute("""
                DELETE FROM hats WHERE id = ?""", [hat.id])
            return True
        return False


class Suppliers:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, supplier):
        self._conn.execute(""" INSERT INTO Suppliers (id,name) VALUES (?,?)""", [supplier.id, supplier.name])

    def find(self, supplier_id):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, name From suppliers WHERE id = ?
            """, [supplier_id])
        return Supplier(*c.fetchone())


class Orders:
    def __init__(self, conn):
        self._conn = conn

    def insert(self, order):
        self._conn.execute(""" INSERT INTO Orders (id,location,hat) VALUES (?,?,?)""",
                           [order.id, order.location, order.hat])

    def find(self, order_id):
        c = self._conn.cursor()
        c.execute("""
            SELECT id, location, name From orders WHERE id = ?
            """, [order_id])
        return Order(*c.fetchone())


class Repository:
    def __init__(self):
        self._conn = sqlite3.connect(sys.argv[4])
        self.hats = Hats(self._conn)
        self.orders = Orders(self._conn)
        self.suppliers = Suppliers(self._conn)

    def close(self):
        self._conn.commit()
        self._conn.close()

    def create_tables(self):
        self._conn.executescript("""
            CREATE TABLE hats (
            id INTEGER PRIMARY KEY,
            topping STRING NOT NULL,
            supplier INTEGER REFERENCES suppliers(id),
            quantity INTEGER NOT NULL );
            
            CREATE TABLE suppliers(
            id INTEGER PRIMARY KEY,
            name STRING NOT NULL);
            
            CREATE TABLE orders(
            id INTEGER PRIMARY KEY,
            location STRING NOT NULL,
            hat INTEGER REFERENCES hats(id));
            """)


repo = Repository()
atexit.register(repo.close)
