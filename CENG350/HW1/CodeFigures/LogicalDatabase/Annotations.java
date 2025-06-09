import java.util.Date;
import java.util.List;

/**
 * Represents a citizen scientist annotation.
 */
public class Annotation {

    // Attributes
    public String annotation_id;
    public User user; // 1..* (A user must have at least one annotation)
    public Subject subject; // 1 (Each annotation belongs to one subject)
    public int count;
    public double timestamp;
    public double confidence_level;
    public Date created_on;

    // Relationships
    public List<Species> species; // 0..* (An annotation can reference multiple species)

    // Constructor
    public Annotation() {}
}
