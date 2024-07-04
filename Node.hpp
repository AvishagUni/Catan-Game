class Node
{
    int id;
    int owner;
    string type;
    vector<Node *> neighbours;

public:
    Node(int i);

    string getType();
    void setType();

    int getOwner();
    void setOwner(int playerNumber);

    vector<Node *> getNeighbours();
    // void setNeighbour(Node *node);

    int getId() const;
};