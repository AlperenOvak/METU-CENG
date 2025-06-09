import java.util.Date;
import java.util.List;

/**
 * Represents a research project in the system.
 */
public class Project {

    // Attributes
    public String project_id;
    public String name;
    public String description;
    public Date start_date;
    public Date end_date;

    // Relationships
    public List<User> users; // 0..* (One project can have multiple users)
    public List<Movie> movies; // 1..* (One project has at least one movie)

    // Constructor
    public Project() {}
}
