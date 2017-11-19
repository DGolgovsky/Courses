struct System
{
    System(string const& uri, string const& data)
        try : db_(uri), dh_(data)
    {
        // Constructor body
    }
    catch (std::exception & e) {
        log("System constructor: ", e);
        throw; // <- compiler add this by default
    }

    Database    db_;
    DataHolder  dh_;
};
