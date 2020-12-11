//
//  MasterViewController.swift
//  Assignment6
//
//  Created by Robbie Korneta on 11/30/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import UIKit
import CoreData

/**
* Controller for the master view table view to display books
********************************************************************************/
class MasterViewController: UITableViewController {

    var managedObjectContext: NSManagedObjectContext? = nil // Object to manipulate and track changes to object
    
    /**
    *   Handles setting up the UI and calling functions to load the view
    ********************************************************************************/
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
     
    }

    /**
    *   Handles setting up the UI and calling functions while view is currently present
    ********************************************************************************/
    override func viewWillAppear(_ animated: Bool) {
        clearsSelectionOnViewWillAppear = splitViewController!.isCollapsed
        super.viewWillAppear(animated)
    }

    // MARK: - Table View

    
    override func numberOfSections(in tableView: UITableView) -> Int {
        
        return fetchedResultsController.sections?.count ?? 0
        
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let sectionInfo = fetchedResultsController.sections![section]
        return sectionInfo.numberOfObjects
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "BookCell", for: indexPath)
        
        configure(cell: cell, for: indexPath)
        
        return cell
    }
    
    /**
    *  Configures the cell UI
    *
    *   @param cell -> The cell to setup
    *   @param indexPath -> The indexpath in the table view to apply the UI
    ********************************************************************************/
    func configure(cell: UITableViewCell, for indexPath: IndexPath) {
        
        // Set cell to the custom book table view cell
        guard let cell = cell as? BookTableViewCell else {
            
            return
            
        }
        
        let book = fetchedResultsController.object(at: indexPath) // Book object at index path
        
        // Set each of the labels
        cell.titleLabel.text = book.title
        cell.authorLabel.text = book.author
        cell.releaseYearLabel.text = book.releaseYear
    }

    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        // Return false if you do not want the specified item to be editable.
        return true
    }

    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        // Handles removal of a book
        if editingStyle == .delete {
            
            let context = fetchedResultsController.managedObjectContext
            context.delete(fetchedResultsController.object(at: indexPath)) // Delete object
                
            do {
                
                try context.save() // Save current context
                
            } catch {
                
                let nserror = error as NSError
                fatalError("Unresolved error \(nserror), \(nserror.userInfo)")
            }
        }
    }
    
    /**
     *  Adds a new book to the database
     *****************************/
    @IBAction func addBook(_ sender: Any) {
        
        // Set up alert
        let alert = UIAlertController(title: "Add Book", message: "Add a new book", preferredStyle: .alert)
        
        // Add text fields for required info
        alert.addTextField {
            textField in
            textField.placeholder = "Title"
        }
        
        alert.addTextField {
            textField in
            textField.placeholder = "Book Author"
        }
        
        alert.addTextField {
            textField in
            textField.placeholder = "Book Release Year"
        }
        
        // Set up action to save data to the database
        let saveAction = UIAlertAction(title: "Save", style: .default) {
            [unowned self] action in
            
            guard let titleTextField = alert.textFields?.first, let authorTextField = alert.textFields?[1], let releaseYearTextField = alert.textFields?.last else {
                return
            }
            
            // Set context to book object
            let context = self.fetchedResultsController.managedObjectContext
            let book = Book(context: context)
            
            // Set variables of the object
            book.title = titleTextField.text ?? ""
            book.author = authorTextField.text ?? ""
            book.releaseYear = releaseYearTextField.text ?? ""
            
            do {
                
                try context.save() // Save context
                
            } catch {
                
                let nserror = error as NSError
                fatalError("Unresolved error \(nserror), \(nserror.userInfo)")
                
            }
        }

        let cancelAction = UIAlertAction(title: "Cancel", style: .default) // Cancel action
        
        // Present the action
        alert.addAction(saveAction)
        alert.addAction(cancelAction)
        present(alert, animated: true)
        
    }
    
    var _fetchedResultsController: NSFetchedResultsController<Book>? = nil // Core data fetch request
    
}

extension MasterViewController: NSFetchedResultsControllerDelegate {
    
    // MARK: - Fetched results controller

    var fetchedResultsController: NSFetchedResultsController<Book> {
        if _fetchedResultsController != nil {
            return _fetchedResultsController!
        }
        
        let fetchRequest: NSFetchRequest<Book> = Book.fetchRequest()
        
        // Set the batch size to a suitable number.
        fetchRequest.fetchBatchSize = 20
        
        // Edit the sort key as appropriate.
        let titleSort = NSSortDescriptor(key: #keyPath(Book.title), ascending: true)
        let authorSort = NSSortDescriptor(key: #keyPath(Book.author), ascending: false)
        let releaseYearSort = NSSortDescriptor(key: #keyPath(Book.releaseYear), ascending: true)
        fetchRequest.sortDescriptors = [titleSort, authorSort, releaseYearSort]
        
        // Edit the section name key path and cache name if appropriate.
        // nil for section name key path means "no sections".
        let aFetchedResultsController = NSFetchedResultsController(fetchRequest: fetchRequest, managedObjectContext: self.managedObjectContext!, sectionNameKeyPath: nil, cacheName: "Master")
        aFetchedResultsController.delegate = self
        _fetchedResultsController = aFetchedResultsController
        
        do {
            try _fetchedResultsController!.performFetch()
        } catch {
             
             let nserror = error as NSError
             fatalError("Unresolved error \(nserror), \(nserror.userInfo)")
        }
        
        return _fetchedResultsController!
    }

    func controllerWillChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        tableView.beginUpdates()
    }

    func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange sectionInfo: NSFetchedResultsSectionInfo, atSectionIndex sectionIndex: Int, for type: NSFetchedResultsChangeType) {
        switch type {
            case .insert:
                tableView.insertSections(IndexSet(integer: sectionIndex), with: .fade)
            case .delete:
                tableView.deleteSections(IndexSet(integer: sectionIndex), with: .fade)
            default:
                return
        }
    }

    func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        switch type {
            case .insert:
                tableView.insertRows(at: [newIndexPath!], with: .fade)
            case .delete:
                tableView.deleteRows(at: [indexPath!], with: .fade)
            case .update:
                let cell = tableView.cellForRow(at: indexPath!) as! BookTableViewCell
                configure(cell: cell, for: indexPath!)
            case .move:
                tableView.deleteRows(at: [indexPath!], with: .automatic)
                tableView.insertRows(at: [newIndexPath!], with: .automatic)
            default:
                return
        }
    }

    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        tableView.endUpdates()
    }
}

