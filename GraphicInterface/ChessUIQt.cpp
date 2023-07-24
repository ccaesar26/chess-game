#include "ChessUIQt.h"
#include "ChessUIQt.h"

#include <QInputDialog>
#include <QMessageBox>

#include "IChessGame.h"
#include "ChessException.h"

#include <QClipboard>
#include <QGuiApplication>

ChessUIQt::ChessUIQt(QWidget *parent)
    : QMainWindow(parent)
{
    game = IChessGame::CreateBoard();

    //Widget containing everything
    QWidget* mainWidget = new QWidget();
    QGridLayout* mainGridLayout = new QGridLayout();
    
    InitializeBoard(mainGridLayout);
    InitializeMessage(mainGridLayout);
    InitializeButtons(mainGridLayout);
    InitializeTimers(mainGridLayout);
    InitializeHistory(mainGridLayout);

    mainWidget->setLayout(mainGridLayout);
    this->setCentralWidget(mainWidget);
}

ChessUIQt::~ChessUIQt()
{
    //No delete?
    //https://doc.qt.io/qt-6/objecttrees.html
}

void ChessUIQt::InitializeMessage(QGridLayout * mainGridLayout)
{
    m_MessageLabel = new QLabel();
    m_MessageLabel->setText("Waiting for white player");
    m_MessageLabel->setAlignment(Qt::AlignCenter);
    m_MessageLabel->setStyleSheet("font-size: 20px; font-weight: bold;");

    mainGridLayout->addWidget(m_MessageLabel, 0, 1, 1, 1);
}

void ChessUIQt::InitializeButtons(QGridLayout* mainGridLayout)
{
    QPushButton* saveButton = new QPushButton("Save");
    QPushButton* loadButton = new QPushButton("Load");
    QPushButton* restartButton = new QPushButton("Restart");
    QPushButton* drawButton = new QPushButton("Draw");
    QPushButton* saveClipboardButton = new QPushButton("Save in Clipboard");

    QWidget* buttonContainer = new QWidget();
    QGridLayout* btnGrid = new QGridLayout();

    btnGrid->addWidget(saveButton, 0, 0);
    btnGrid->addWidget(loadButton, 0, 1);
    btnGrid->addWidget(restartButton, 0, 2);
    btnGrid->addWidget(drawButton, 0, 3);

    btnGrid->addWidget(saveClipboardButton, 0, 4);

    connect(saveButton, &QPushButton::pressed, this, &ChessUIQt::OnSaveButtonClicked);
    connect(loadButton, &QPushButton::pressed, this, &ChessUIQt::OnLoadButtonClicked);
    connect(restartButton, &QPushButton::pressed, this, &ChessUIQt::OnRestartButtonClicked);
    connect(drawButton, &QPushButton::pressed, this, &ChessUIQt::OnDrawButtonClicked);

    connect(saveClipboardButton, &QPushButton::pressed, this, &ChessUIQt::SaveInClipboard);

    buttonContainer->setLayout(btnGrid);
    mainGridLayout->addWidget(buttonContainer, 0, 0, 1, 1);
}

void ChessUIQt::InitializeTimers(QGridLayout* mainGridLayout)
{
    QWidget* timerContainer = new QWidget();
    QGridLayout* timerGrid = new QGridLayout();

    QLabel* blackTimerLbl = new QLabel("Black timer: ");
    m_BlackTimer = new QLabel("00:00:00");

    QPushButton* pauseTimerBtn = new QPushButton(" Pause | Resume");
    //TODO Create slot and connect button

    QLabel* whiteTimerLbl = new QLabel("    White timer: ");
    m_WhiteTimer = new QLabel("00:00:00");

    timerContainer->setFixedWidth(400);

    timerGrid->addWidget(blackTimerLbl, 0, 0);
    timerGrid->addWidget(m_BlackTimer, 0, 1);
    timerGrid->addWidget(pauseTimerBtn, 0, 2);
    timerGrid->addWidget(whiteTimerLbl, 0, 3);
    timerGrid->addWidget(m_WhiteTimer, 0, 4);

    timerContainer->setLayout(timerGrid);
    mainGridLayout->addWidget(timerContainer, 2, 0, 1, 2, Qt::AlignCenter);
}

void ChessUIQt::InitializeHistory(QGridLayout* mainGridLayout)
{
    m_MovesList = new QListWidget();
    m_MovesList->setMinimumWidth(250);
    m_MovesList->setMaximumWidth(350);
    connect(m_MovesList, &QListWidget::itemActivated, this, &ChessUIQt::OnHistoryClicked);
    mainGridLayout->addWidget(m_MovesList, 1, 0, 1, 1);
}

void ChessUIQt::InitializeBoard(QGridLayout* mainGridLayout)
{
    QGridLayout* chessGridLayout;
    chessGridLayout = new QGridLayout();
    QWidget* board = new QWidget();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_grid[i][j] = new GridButton({ i,j }, PieceType::none, PieceColor::none);
            chessGridLayout->addWidget(m_grid[i][j], i, j, 1, 1);
            connect(m_grid[i][j], &GridButton::Clicked, this, &ChessUIQt::OnButtonClicked);
        }
    }

    board->setLayout(chessGridLayout);
    mainGridLayout->addWidget(board, 1, 1, 1, 1);
}

void ChessUIQt::OnButtonClicked(const std::pair<int, int>&position)
{
    //At second click
    if (m_selectedCell.has_value()) 
    {
        if (m_selectedCell.value() == position)
        {
            m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
            m_selectedCell.reset();
            UnhighlightPossibleMoves(game->GetMoves(position.first, position.second));
        }
        else
        {
            //TODO COMPLETE ME...
            try
            {
                game->MakeMovement(m_selectedCell->first, m_selectedCell->second, position.first, position.second);
                
                if (game->IsWaitingForUpgrade())
                {
                    ShowPromoteOptions();
                }

                switch (game->GetCurrentPlayer())
                {
                case EColor::Black:
                    UpdateMessage("Waiting for black player");
                    break;
				case EColor::White:
					UpdateMessage("Waiting for white player");
					break;
                default:
                    break;
                }
            }
            catch (const OccupiedByOwnPieceException& e)
            {
                UnhighlightPossibleMoves(game->GetMoves(m_selectedCell->first, m_selectedCell->second));

				m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
				m_selectedCell.reset();                

				m_selectedCell = position;
				m_grid[position.first][position.second]->setSelected(true);

				HighlightPossibleMoves(game->GetMoves(m_selectedCell->first, m_selectedCell->second));

                return;
            }
            catch (const ChessException& e)
            {
                return;
            }

            //Unselect prev. pressed button
            m_grid[m_selectedCell.value().first][m_selectedCell.value().second]->setSelected(false);
            m_selectedCell.reset();

			UpdateBoard();
            if (game->IsGameOver())
            {
                if (game->IsDraw())
                {
					m_MessageLabel->setText("Game over! Draw.");
					QMessageBox::StandardButton reply;
					reply = QMessageBox::question(this, "Game Over", "Draw.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);

					if (reply == QMessageBox::Yes)
					{
						OnRestartButtonClicked();
					}
					else
					{
						Exit();
					}
                    return;
                }
				m_MessageLabel->setText("Game over! Black player won");
				QMessageBox::StandardButton reply;
				
				if (game->IsWonByBlackPlayer())
				{
                    reply = QMessageBox::question(this, "Game Over", "Black player won.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);
                }
				if (game->IsWonByWhitePlayer())
				{
					reply = QMessageBox::question(this, "Game Over", "White player won.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);
				}
                
                if (reply == QMessageBox::Yes)
				{
                    OnRestartButtonClicked();
				}
				else
				{
                    Exit();
				}
				return;
            }
			
        }
    }
    //At first click
    else 
    {
        m_selectedCell = position;
        m_grid[position.first][position.second]->setSelected(true);

        //TODO Show possible moves here
        HighlightPossibleMoves(game->GetMoves(position.first, position.second));
    }
}

void ChessUIQt::OnSaveButtonClicked()
{
    //TODO ...

}

void ChessUIQt::OnLoadButtonClicked()
{
    //TODO ...
}

void ChessUIQt::OnRestartButtonClicked()
{
    //game.reset();
	game = IChessGame::CreateBoard();

	//Widget containing everything
	QWidget* mainWidget = new QWidget();
	QGridLayout* mainGridLayout = new QGridLayout();

	InitializeBoard(mainGridLayout);
	InitializeMessage(mainGridLayout);
	InitializeButtons(mainGridLayout);
	InitializeTimers(mainGridLayout);
	InitializeHistory(mainGridLayout);

	mainWidget->setLayout(mainGridLayout);
	this->setCentralWidget(mainWidget);

    StartGame();
}

void ChessUIQt::OnDrawButtonClicked()
{
    //TODO MODIFY ME
    game->RequestDraw();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Draw proposal", "Do you accept a draw?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) 
    {
		game->AcceptDrawProposal();
		m_MessageLabel->setText("Game over! Draw.");
		QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Game Over", "Draw.\nDo you want to play again?", QMessageBox::Yes | QMessageBox::Close);
		
		if (reply == QMessageBox::Yes)
		{
			OnRestartButtonClicked();
		}
		else
		{
			Exit();
		}
		return;
        
    }
    else
    {
        game->DeclineDrawProposal();
    }
}

void ChessUIQt::SaveInClipboard()
{
    QString textToCopy;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            PieceType type = m_grid[i][j]->GetType();
            PieceColor color = m_grid[i][j]->GetColor();

            char piece;

			switch (type) {
			case PieceType::none:
                piece = ' ';
				break;
			case PieceType::king:
                piece = 'k';
				break;
			case PieceType::rook:
                piece = 'r';
				break;
			case PieceType::bishop:
                piece = 'b';
				break;
			case PieceType::queen:
                piece = 'q';
				break;
			case PieceType::knight:
                piece = 'h';
				break;
			case PieceType::pawn:
                piece = 'p';
				break;
			default:
                piece = '*';
				break;
			}

            if (color == PieceColor::black)
                piece = std::toupper(piece);   // include to upper if it doesn t work //

            textToCopy.append("\'");
            textToCopy.append(piece);
            textToCopy.append("\', ");
        }
        textToCopy.append("\n");
    }
    textToCopy.chop(3);
    
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText(textToCopy);
}

void ChessUIQt::OnHistoryClicked(QListWidgetItem* item)
{
    int index = m_MovesList->currentRow();
    
    //TODO ...
}

void ChessUIQt::UpdateHistory()
{
    m_MovesList->clear();

    //TODO modify me...
    int numMoves = 10;
    for (int i = 0; i < numMoves; i++) {
        m_MovesList->addItem("#1   Color: Black   Move: A1 A2");
    }
}

void ChessUIQt::UpdateBoard()
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            std::pair<PieceType, PieceColor> newPiece;

            if (game->GetIPiecePtr(i, j))
            {
				switch (game->GetIPiecePtr(i, j)->GetType())
				{
				case EType::Rook:
					newPiece.first = PieceType::rook;
					break;
				case EType::Horse:
					newPiece.first = PieceType::knight;
					break;
				case EType::Bishop:
					newPiece.first = PieceType::bishop;
					break;
				case EType::Queen:
					newPiece.first = PieceType::queen;
					break;
				case EType::King:
					newPiece.first = PieceType::king;
					break;
				case EType::Pawn:
					newPiece.first = PieceType::pawn;
					break;
				default:
					break;
				}

                switch (game->GetIPiecePtr(i, j)->GetColor())
				{
				case EColor::Black:
					newPiece.second = PieceColor::black;
					break;
				case EColor::White:
					newPiece.second = PieceColor::white;
					break;
				default:
					break;
				}
            }
            else
            {
                newPiece.first = PieceType::none;
				newPiece.second = PieceColor::none;
            }
            
            m_grid[i][j]->setPiece(newPiece);
			m_grid[i][j]->setSelected(false);
			m_grid[i][j]->setHighlighted(false);
        }
    }

}

void ChessUIQt::HighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
    for (const auto& position : possibleMoves) {
        m_grid[position.first][position.second]->setHighlighted(true);
    }
}

void ChessUIQt::UnhighlightPossibleMoves(const std::vector<std::pair<int, int>>& possibleMoves)
{
	for (const auto& position : possibleMoves) {
		m_grid[position.first][position.second]->setHighlighted(false);
	}
}

void ChessUIQt::StartGame()
{
    //TODO MODIFY ME OR DELETE ME
    UpdateBoard();
}

void ChessUIQt::ShowPromoteOptions()
{
    QInputDialog dialog;
    QList<QString> options;
    options.append("Rook");
    options.append("Bishop");
    options.append("Queen");
    options.append("Knight");

    dialog.setComboBoxItems(options);
    dialog.setModal(true);

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Pawn promote"),
        tr("Promote pawn to: "), options, 0, false, &ok);

    if (ok && !item.isEmpty())
    {
        //TODO
        game->UpgradePawn(item.toStdString());
        //game.promotePawn(parseQStringToPieceType(item))

        ////TODO DELETE ME...
        //QMessageBox notification;
        //notification.setText("You selected " + item);
        //notification.exec();
    }
}

void ChessUIQt::UpdateMessage(const QString& message)
{
    m_MessageLabel->setText(message);
}

