
import java.io.*;
import java.util.*;

/**
 * 
 */
public class User Interface {

    /**
     * Default constructor
     */
    public User Interface() {
    }

    /**
     * 
     */
    public String user_id;

    /**
     * 
     */
    public String username;

    /**
     * 
     */
    public Enum Citizen Scientist Researcher Admin role;

    /**
     * 
     */
    public String session token;

    /**
     * @param username 
     * @param password 
     * @return
     */
    public Boolean login(String username, String password) {
        // TODO implement here
        return null;
    }

    /**
     * @param session_token 
     * @return
     */
    public Void logout(String session_token) {
        // TODO implement here
        return null;
    }

    /**
     * @param user_id 
     * @param media_id 
     * @param species 
     * @return
     */
    public Boolean submit_annotation(String user_id, String media_id, String species) {
        // TODO implement here
        return null;
    }

    /**
     * @param user_id 
     * @param media_id 
     * @return
     */
    public JSON retrieve_results(String user_id, String media_id) {
        // TODO implement here
        return null;
    }

    /**
     * @param user_id 
     * @param file 
     * @return
     */
    public Boolean upload_footage(String user_id, Binary file) {
        // TODO implement here
        return null;
    }

}