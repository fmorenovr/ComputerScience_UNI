# list of directorys, in my spacework

list.dirs <- function(path=".",recursive=FALSE) {
    get.list <- list.files(path)
    if (length(get.list) == 0) {return(NULL)} #no files or directories
    get.list.fixed <- paste(path,get.list,sep="/")
    whichonesaredir <- file.info(get.list.fixed)$isdir
    if (!any(whichonesaredir)) {return(NULL)} #no directories, only files
    dirlist <- get.list.fixed[whichonesaredir]
    finaldirlist <- dirlist
    if ((recursive & length(dirlist) > 0)) {
      for (i in 1:length(dirlist)) {
         finaldirlist <- c(finaldirlist,list.dirs(dirlist[i],recursive))
      }
    }
    return(finaldirlist)
}
