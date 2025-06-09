import java.util.Date;
import java.util.List;

/**
 * Represents a user in the system.
 */
public class User {

    // Attributes
    public String user_id;
    public String username;
    public String email;
    public String password_hash;
    public String role; // "Citizen Scientist", "Researcher", "Admin"
    public Date date_registered;

    // Relationships
    public List<Annotation> annotations; // 1..* (A user must have at least one annotation)
    public List<Project> projects; // 0..* (A user may belong to multiple projects)

    // Constructor
    public User() {}
}
