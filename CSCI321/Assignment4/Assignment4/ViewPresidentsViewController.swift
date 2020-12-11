//
//  ViewPresidentsViewController.swift
//  Assignment4
//
//  Created by Robbie Korneta on 11/5/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import UIKit

class ViewPresidentsViewController: UIViewController {

    @IBOutlet weak var tableView: UITableView!
    
    var objects = [President]()         // Array of presidents
    var filteredObjects = [President]() // Filtered array of presidents
    
    let searchController = UISearchController(searchResultsController: nil) // Initialize search controller

    /*
     *  Handles the UI upon the view loading
     */
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        loadFile()              // Load plist file of presidents
        setUpSearchController() // Set up the search controller
        
    }

    override func viewWillAppear(_ animated: Bool) {
        
        super.viewWillAppear(animated)
        
    }
    
    /*
     *  Loads the plist file into the objects array and displays to table view
     */
    func loadFile() {
        
        // Get the file from the project
        guard let path = Bundle.main.path(forResource: "presidents", ofType: "plist"), let xml = FileManager.default.contents(atPath: path) else {
            
            fatalError("Unable to access property list presidents.plist")
            
        }
        
        // Inserts the list of presidents from the array into the objects array
        // Then, sort the array of presidents based on their number in presidency
        do {
            
            objects = try PropertyListDecoder().decode([President].self, from: xml)
            
            objects.sort {
                
                return $0.number < $1.number
                
            }
            
        } catch {
            
            fatalError("Unable to decode property list presidents.plist")
        }
        
        tableView.reloadData() // Reload table view to display presidents
        
    }
    
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
        
        if segue.identifier == "PresidentDetails" { // Check for which segue is being performed
            
            // Get the current row that is being selected
            if let indexPath = tableView.indexPathForSelectedRow {
                
                let object: President // Create president object
                
                // Check for if the results are being filtered
                if isFiltering() {
                    
                    object = filteredObjects[indexPath.row] // If they are, select based on filtered array
                    
                } else {
                    
                    object = objects[indexPath.row] // If not, select based on all presidents array
                    
                }
                
                let controller = segue.destination as! PresidentDetailViewController // Destination view controller
                
                // Set each variable in the next view controller to the respective values
                controller.presidentName = object.name
                controller.number = object.number
                controller.startDate = object.startDate
                controller.endDate = object.endDate
                controller.nicknames = object.nickname
                controller.politicalParty = object.politicalParty
                
            }
            
        }
        
    }

}

extension ViewPresidentsViewController: UISearchControllerDelegate, UISearchBarDelegate, UISearchResultsUpdating {
    
    /*
     *  Sets up the search controller to be displayed
     */
    
    func setUpSearchController() {
        
        searchController.searchResultsUpdater = self // Object responsible for updating contents
        searchController.obscuresBackgroundDuringPresentation = false //Will not obscure background
        searchController.searchBar.placeholder = "Search Presidents" // Placeholder for search bar
        navigationItem.searchController = searchController // search controller to integrate
        definesPresentationContext = true  // View will be covered
        searchController.searchBar.scopeButtonTitles = ["All", "Democrat", "Republican", "Whig"] // Scope bar button titles for filtering
        searchController.delegate = self // Set delegate of search controller
        searchController.searchBar.delegate = self // Set delegate of search bar
        
    }
    
    // Check to see if search bar is empty
    func searchBarIsEmpty() -> Bool {
        
        return searchController.searchBar.text?.isEmpty ?? true
    }
    
    /*
     *  Check to see if the search controller is actively being interacted with to determine
     *  whether or not filtering is active
     *
     *  Returns true if the search controller is being interacted with
     */
    func isFiltering() -> Bool {
        
        let searchBarScopeIsFiltering = searchController.searchBar.selectedScopeButtonIndex != 0
        
        return searchController.isActive && (!searchBarIsEmpty() || searchBarScopeIsFiltering)
        
    }
    
    /*
     *  Filters the results of the user entered data
     *
     *  @param searchText -> The text entered by the user into the search bar
     *  @param scope      -> The scope bar item that is selected
     *
     */
    func filterContentForSearchText(_ searchText: String, scope: String = "All") {
        
        // Filter matching objects based on user input
        filteredObjects = objects.filter { president in
            
            // Boolean to see if the object matches user input
            let doesPartyMatch = (scope == "All") || (president.politicalParty == scope)
            
            // Check for search bar empty
            if searchBarIsEmpty() {
                
                return doesPartyMatch
                
            } else {
                
                return doesPartyMatch && president.name.lowercased().contains(searchText.lowercased())
                
            }
        }
        
        tableView.reloadData() // Reload table view with updated results
        
    }
    
    // Called when search bar becomes first responder
    // Handles filtering
    func updateSearchResults(for searchController: UISearchController) {
        
        let searchBar = searchController.searchBar // Search bar being used
        let scope = searchBar.scopeButtonTitles![searchBar.selectedScopeButtonIndex] // Scope bar selected
        
        filterContentForSearchText(searchController.searchBar.text!, scope: scope) // Filter
        
    }

    // If scope bar item changes this will be called
    func searchBar(_ searchBar: UISearchBar, selectedScopeButtonIndexDidChange selectedScope: Int) {
        
        filterContentForSearchText(searchBar.text!, scope: searchBar.scopeButtonTitles![selectedScope]) // Filter results
        
    }
    
}

extension ViewPresidentsViewController: UITableViewDelegate, UITableViewDataSource {
    
    // Number of rows to display in table view
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        // If filtering is active, only display filtered amount of cells
        if isFiltering() {
            
            return filteredObjects.count
            
        } else { // Display all cells
            
            return objects.count
            
        }
        
    }
    
    // Handles the UI layout of each cell
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        let cell = tableView.dequeueReusableCell(withIdentifier: "PresidentTableViewCell", for: indexPath) as! PresidentTableViewCell // Set cell to custom table view cell
        
        let object: President // Create president object
        
        // If currently filtering, the UI for the cell will match the filtered array
        if isFiltering() {
            
            object = filteredObjects[indexPath.row]
            
        } else { // UI for cell matches all presidents array
            
            object = objects[indexPath.row]
            
        }
        
        cell.presidentNameLabel.text = object.name // Set name label of president
        cell.politicalAffiliationLabel.text = object.politicalParty // Set politcal party label of president
        
        return cell
        
    }
    
    // Handles when a row is selected
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        let president: President // Create president object
        
        if isFiltering() { // If filtering is active, the selected row is based on filtered array
            
            president = filteredObjects[indexPath.row]
            self.performSegue(withIdentifier: "PresidentDetails", sender: president)
            
        } else { // Selected row based on all presidents array
            
            president = objects[indexPath.row]
            self.performSegue(withIdentifier: "PresidentDetails", sender: president)
            
        }
        
    }
    
}
