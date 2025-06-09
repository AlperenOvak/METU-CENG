import java.util.List;

/**
 * Represents a species classification option.
 */
public class Species {

    // Attributes
    public String species_id;
    public String name;
    public String common_name;
    public String taxonomy_group;

    // Relationships
    public List<Annotation> annotations; // 0..* (One species can be in multiple annotations)

    // Constructor
    public Species() {}
}
