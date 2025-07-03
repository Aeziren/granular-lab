namespace CookBook {
    public abstract class Ingredient {
        protected readonly int _id;
        public int Id {
            get => _id;
        }

        protected readonly string _name = "";
        public string Name {
            get => _name;
        }

        protected readonly string _instructions = "";
        public string Instructions {
            get => _instructions;
        }

        public void Print() {
            Console.WriteLine($"{Id}. {Name}");
        }

        protected Ingredient(int id, string name, string instructions) {
            _id = id;
            _name = name;
            _instructions = instructions;
        }
    }

    class Wheat : Ingredient {
        public Wheat() : base(1, "Wheat", "Sieve. Add to other ingredients.") { }
    }

    class Coconut : Ingredient, IFlour {

    }
}

