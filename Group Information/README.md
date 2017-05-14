grinfo    [ -c  <count> |  -g  < group name>  |  -u   <user login name>  | -n  <substring>  |  -ac  <count>  | -ag  <group name > ]  

–c option:
          Display the number of groups with memberships of at least <count>.
          For each such group, it displays the group membership count, its GID and its name.
 
 –g option:
          Display the <group name> GID and its membership count. 
          For each member of the group, it displays its login, UIN and name (or <NULL> if name field is empty).
          The listing is sorted by UIN field (older accounts usually has smaller UIN).
 
  –u option:
          Display the user name (or <NULL>), the main group name and the augmented group names (if any).
 
  –n option:
           Display the count of users whose login or name matches <substring>.
           For each matching user it lists its login and its name (or NULL).
          
  –ac option:
           Display the number of augmented groups that have added members of at least <count>.
            For each such group, it displays the group membership count, its GID and its name.
 
  –ag option:
          Display the augmented <group name> GID and its membership count. 
          For each member of the group, it displays its login, its main group name and its name (or <NULL> if name field is empty).
 
 If no specified option :   Shows how to use the command and its options
