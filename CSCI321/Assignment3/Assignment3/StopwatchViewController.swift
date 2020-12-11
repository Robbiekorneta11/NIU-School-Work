//
//  StopwatchViewController.swift
//  Assignment3
//
//  Created by Robbie Korneta on 10/15/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//
//  Implemented all extra credit portions (Hours being display/not being displayed, custom font, pause and start button will switch)

import UIKit

class StopwatchViewController: UIViewController {

    @IBOutlet weak var startButton: UIBarButtonItem! //The start button to start the timer
    @IBOutlet weak var stopButton: UIBarButtonItem!  //The stop button to stop the timer
    @IBOutlet weak var timerPicker: UIDatePicker!    //The picker view to select the time
    @IBOutlet weak var timerLabel: UILabel!          //Label to display the time left
    
    var timer: Timer? = nil //Timer object
    var timeLeft = 60.00    //The time remaining on the timer in seconds
    var paused = true       //Checks to see if it is paused
    var stopped = true      //Check to see if the time is stopped
    
    /*
     *  When the view is first pulled up, this updates the UI
     */
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        let timeLeftString = "01:00"
        timerLabel.text = timeLeftString //Set the test to the amount of time left (by default 1 minute)
        stopButton.isEnabled = false //Disable stop button because timer is not running

        // Do any additional setup after loading the view.
    }
    
    /*
     *  Handles the start button or pause being pressed
     */
    
    @IBAction func startTimer(_ sender: Any) {
        
        stopButton.isEnabled = true //Enable the stop button
        
        //Check to see if the timer has been paused
        //If it is, then the play button should appear
        //If it not, then the pause button should appear
        if paused {
            
            paused = false //Set paused to false because the timer is running
            timer = Timer.scheduledTimer(timeInterval: 1, target: self, selector: #selector(decrementTimer), userInfo: nil, repeats: true) //Begin the timer
            startButton.image = UIImage(systemName: "pause.fill") //Set bar button image to a pause button
            stopped = false //Stopped is false because it is running
            
        } else if !paused {
            
            timer?.invalidate() //Pause the timer
            paused = true //The timer is paused
            stopped = false //However, it is not fully stopped
            startButton.image = UIImage(systemName: "play.fill") //Set image to the play button
            
        }
        
    }
    
    /*
     *  Handles the stop button being pressed
     */
    
    @IBAction func stopTimer(_ sender: Any) {
        
        timer?.invalidate() //Stop the timer
        timeLeft = timerPicker.countDownDuration //Update time left to the picker selected time
        stopped = true //The timer is stopped
        paused = true //It is also technically paused
        
        let hours = Int(timeLeft) / 3600 //Calculate hours
        let minutes = Int(timeLeft) / 60 % 60 //Calculate minutes
        let seconds = Int(timeLeft) % 60 //Calculate seconds
        
        var timeLeftString = String(format:"%02i:%02i:%02i", hours, minutes, seconds)
        
        //Determine how the string should be formatted based on the amount of seconds that are left
        
        if (timeLeft >= 3600) {
            
            timeLeftString = String(format:"%02i:%02i:%02i", hours, minutes, seconds)
            
        } else if (timeLeft < 3600) {
            
            timeLeftString = String(format:"%02i:%02i", minutes, seconds)
            
        }
        
        startButton.image = UIImage(systemName: "play.fill") //Set the start button image
        stopButton.isEnabled = false //Disable stop button
        timerLabel.text = timeLeftString //Update the timer label
        
    }
    
    /*
     *  Handles the picker view to update the timer value
     */
    
    @IBAction func selectTime(_ sender: Any) {
        
        //If the timer is stopped, then when the timer is changed it will updated the timer value
        
        if stopped {
        
            timeLeft = timerPicker.countDownDuration
            
            let hours = Int(timeLeft) / 3600
            let minutes = Int(timeLeft) / 60 % 60
            let seconds = Int(timeLeft) % 60
            
            var timeLeftString = String(format:"%02i:%02i:%02i", hours, minutes, seconds)
            
            //Determine how the string should be formatted based on the amount of seconds that are left
            
            if (timeLeft >= 3600) {
                
                timeLeftString = String(format:"%02i:%02i:%02i", hours, minutes, seconds)
                
            } else if (timeLeft < 3600) {
                
                timeLeftString = String(format:"%02i:%02i", minutes, seconds)
                
            }
            
            timerLabel.text = timeLeftString
            
        }
        
    }
    
    /*
     *  Decrements the timer
     */
    
    @objc func decrementTimer() {
        
        timeLeft -= 1.0 //Decrement the amount of seconds remaining by 1
        
        let hours = Int(timeLeft) / 3600
        let minutes = Int(timeLeft) / 60 % 60
        let seconds = Int(timeLeft) % 60
        
        var timeLeftString = String(format:"%02i:%02i:%02i", hours, minutes, seconds)
        
        //Determine how the string should be formatted based on the amount of seconds that are left
        
        if (timeLeft >= 3600) {
            
            timeLeftString = String(format:"%02i:%02i:%02i", hours, minutes, seconds)
            
        } else if (timeLeft < 3600) {
            
            timeLeftString = String(format:"%02i:%02i", minutes, seconds)
            
        }
        
        timerLabel.text = timeLeftString
        //If there is no time left, stop the timer
        if (timeLeft <= 0) {
            
            timer?.invalidate()
            
        }
        
    }

}
